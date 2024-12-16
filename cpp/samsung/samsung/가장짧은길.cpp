#if 0
#define _CRT_SECURE_NO_WARNINGS

#define INF 8999999999999999999 // longlong최대값
#include <iostream>

struct Edge {
	int link;
	long long last_cost;
	long long cost;

	Edge(int a=0, int b = 0):link(a), cost(b), last_cost(0){}

	bool operator<(const Edge& other) {
		return cost < other.cost;
	}
};

template<typename T>
struct Stack {
	T* data;
	int size;
	int capasity;

	Stack(int init = 2) :size(0), capasity(init) {
		data = new T[init];
	}

	~Stack() {
		delete[] data;
	}

	void resize(int new_capa) {
		T* new_data = new T[new_capa];
		for (int i = 0; i < size; ++i) {
			new_data[i] = data[i];
		}
		delete[] data;
		data = new_data;
		capasity = new_capa;
	}

	void clear() { size = 0; }

	void push(T value) {
		if (size == capasity) resize(capasity * 2);
		data[size++] = value;
	}

	T operator[](int index) { return data[index]; }
};

template<typename T>
struct Heap {
	T* data;
	int size;
	int capasity;

	Heap(int init = 2) :size(0), capasity(init) {
		data = new T[init];
	}

	~Heap() {
		delete[] data;
	}

	void resize(int new_capa) {
		T* new_data = new T[new_capa];
		for (int i = 0; i < size; ++i) {
			new_data[i] = data[i];
		}
		delete[] data;
		data = new_data;
		capasity = new_capa;
	}

	void clear() { size = 0; }

	void push(T value) {
		if (size == capasity) resize(capasity * 2);

		int childidx = size;

		while (childidx > 0) {
			int paridx = (childidx - 1) >> 1;
			T par = data[paridx];

			if (value < par) {
				data[childidx] = par;
				childidx = paridx;
				continue;
			}
			break;
		}
		data[childidx] = value;
		++size;
	}

	T pop() {
		T returnvalue = data[0];
		T lastitem = data[--size];

		int par = 0;
		int child = 1;

		while (child < size) {
			int right = child + 1;
			if (right < size && !(data[child] < data[right])) child = right;
			
			if (data[child] < lastitem) {
				data[par] = data[child];
				par = child;
				child = (par << 1) + 1;
				continue;
			}
			break;
		}

		data[par] = lastitem;
		return returnvalue;
	}
};

int N, M;
long long distance[200001];
long long last_dis[200001];
Stack<Edge> node[200001];
Heap<Edge> heap;

long long solve() {
	std::cin >> N >> M;
	for (int i = 1; i <= N; ++i) {
		distance[i] = INF;
		node[i].clear();
		last_dis[i] = -1;
	}
	heap.clear();

	for (int i = 0; i < M; ++i) {
		int a, b, c;
		std::cin >> a >> b >> c;
		node[a].push(Edge(b, c));
		node[b].push(Edge(a, c));
	}

	distance[1] = 0;
	last_dis[1] = 0;

	// last_cost는 0으로 초기화 되므로 그냥 push
	for (int i = 0; i < node[1].size; ++i)	heap.push(node[1][i]);


	while (heap.size) {
		Edge now = heap.pop();

		if (distance[now.link] < now.cost) continue;
		if (distance[now.link] == now.cost) {
			if (last_dis[now.link] < now.last_cost)
				last_dis[now.link] = now.last_cost;
			continue;
		}
		distance[now.link] = now.cost;
		last_dis[now.link] = now.last_cost;
		
		for (int i = 0; i < node[now.link].size; ++i) {
			Edge next = node[now.link][i];
			if (distance[next.link] < now.cost + next.cost) continue;
			if (distance[next.link] == now.cost + next.cost) {
				if (last_dis[next.link] < now.cost) last_dis[next.link] = now.cost;
				continue;
			}

			next.last_cost = now.cost;
			next.cost = now.cost + next.cost;
			heap.push(next);
		}
	}

	long long cost = 0;
	for (int i = 1; i <= N; ++i) {
		cost += distance[i];
		cost -= last_dis[i];
	}

	return cost;

}


int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	freopen("가장빠른길_input.txt", "r", stdin);

	int T;
	std::cin >> T;

	for (int tc = 1; tc <= T; ++tc) {
		std::cout << "#" << tc << " " << solve() << "\n";
	}
}
#endif