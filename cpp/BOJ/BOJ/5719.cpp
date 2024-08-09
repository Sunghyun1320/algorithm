#if 0
#include <iostream>
#define INF 1234567890

template<typename T>
struct stack {
	T *data;
	size_t _size;
	size_t capasity;
	
	stack(size_t init_size = 2) :_size(0), capasity(init_size) {
		data = new T[capasity];
	}
	~stack() {
		delete[] data;
	}


	int size() {
		return static_cast<int>(_size);
	}

	void clear() {
		_size = 0;
	}

	void resize(size_t a) {
		T * new_data = new T[a];
		for (size_t i = 0; i < _size; i++) {
			new_data[i] = data[i];
		}
		delete[] data;
		data = new_data;
		capasity = a;
	}

	void push(T value) {
		if (_size == capasity) {
			resize(_size * 2);
		}

		data[_size++] = value;
	}

	T pop() {
		if (_size == 0) {
			std::cerr << "index error : stack empty";
			std::exit(EXIT_FAILURE);
		}

		return data[--_size];
	
	}

	T& operator[](size_t index) {
		if (index >= _size) {
			std::cerr << "index error : size over";
			std::exit(EXIT_FAILURE);
		}

		return data[index];
	}

};

template<typename T>
struct heapq {
	T* data;
	size_t _size;
	size_t capasity;

	heapq(size_t init_size = 2) : _size(0), capasity(init_size) {
		data = new T[capasity];
	}

	~heapq() {
		delete[] data;
	}

	int size() {
		return static_cast<int>(_size);
	}

	void resize(size_t a) {
		T * new_data = new T[a];
		for (size_t i = 0; i < _size; i++) {
			new_data[i] = data[i];
		}
		delete[] data;
		data = new_data;
		capasity = a;
	}

	void push(T value) {
		if (_size == capasity) resize(capasity * 2);
		size_t child = _size;

		while (child > 0) {
			int parindex = (child - 1) >> 1;
			T parent = data[parindex];

			if (value < parent) {
				data[child] = parent;
				child = parindex;
				continue;
			}
			break;
		}

		data[child] = value;
		++_size;
	}

	T pop() {
		if (_size == 0) {
			std::cerr << "index error : heap empty";
			std::exit(EXIT_FAILURE);
		}

		T returnitem = data[0];
		T lastitem = data[--_size];
		data[0] = lastitem;

		int par = 0;

		int child = (par << 1) + 1;
		while (child < size()) {
			int right = child + 1;
			if (right < size() && !(data[child] < data[right])) child = right;

			if (data[child] < lastitem) {
				data[par] = data[child];
				par = child;
				child = (par << 1) + 1;
				continue;
			}
			break;
		}

		data[par] = lastitem;
		return returnitem;
	}

};

struct edge {
	int target;
	int cost;
	edge(int a=0, int b=0) :target(a), cost(b) {}
	bool operator<(const edge& other)const {
		return cost < other.cost;
	}

};

struct Cost {
	int min_cost;
	stack<int> min_path;
};


int n, m, s, d;
Cost cost[500];
bool min_path[500][500];
stack<edge> node[500];
stack<int> dfs;
bool visit[500];

void dijkstra() {
	heapq<edge> heap;

	cost[s].min_cost = 0;
	heap.push(edge(s, 0));

	while (heap.size()) {
		edge now = heap.pop();

		for (int i = 0; i < node[now.target].size(); i++) {
			edge temp = node[now.target][i];
			if (min_path[now.target][temp.target]) continue;
			if (cost[temp.target].min_cost < now.cost + temp.cost) continue;
			else if (cost[temp.target].min_cost == now.cost + temp.cost)
				cost[temp.target].min_path.push(now.target);
			else {
				cost[temp.target].min_cost = now.cost + temp.cost;
				cost[temp.target].min_path.clear();
				cost[temp.target].min_path.push(now.target);
				heap.push(edge(temp.target, now.cost + temp.cost));
			}
		}

	}
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	while (1) {
		std::cin >> n >> m;
		if (!n) break;

		std::cin >> s >> d;

		//전역변수 초기화
		dfs.clear();
		for (int i = 0; i < n; i++) {
			node[i].clear();
			cost[i].min_cost = INF;
			cost[i].min_path.clear();
			for (int j = 0; j < n; j++)
				min_path[i][j] = false;
		}

		for (int i = 0; i < m; i++) {
			int a, b, c;
			std::cin >> a >> b >> c;
			node[a].push(edge(b, c));
		}

		// 다익스트라를 통해서 목표 경로까지 최단 경로를 탐색
		dijkstra();


		dfs.push(d);

		for (int i = 0; i < n; i++) {
			visit[i] = false;
		}


		while (dfs.size()) {
			int now = dfs.pop();
			if (visit[now]) continue;
			visit[now] = true;

			for (int i = 0; i < cost[now].min_path.size(); i++) {
				int temp = cost[now].min_path[i];
				//visit[temp] = true;
				min_path[temp][now] = true;
				dfs.push(temp);
			}
		}

		for (int i = 0; i < n; i++) {
			cost[i].min_cost = INF;
			cost[i].min_path.clear();
		}

		dijkstra();

		if (cost[d].min_cost == INF) cost[d].min_cost = -1;
		//std::cout << "################## : ";
		std::cout << cost[d].min_cost << "\n";

	}

}

#endif