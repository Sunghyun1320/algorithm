#if 0
#define _CRT_SECURE_NO_WARNINGS
#define INF 987654321

#include <iostream>

template<typename T>
struct Heap {
	T* data;
	int size;
	int capasity;

	Heap(int init_capa = 2) : size(0), capasity(init_capa) {
		data = new T[init_capa];
	}

	~Heap() {
		delete[] data;
	}

	void clear() { size = 0; }
	void resize(int new_capa) {
		T* new_data = new T[new_capa];
		for (int i = 0; i < size; ++i) 
			new_data[i] = data[i];
		delete[] data;
		data = new_data;
		capasity = new_capa;
	}

	void push(T value) {
		if (size == capasity) resize(capasity * 2);
		int child = size;

		while (child > 0) {
			int par = (child - 1) >> 1;

			if (value < data[par]) {
				data[child] = data[par];
				child = par;
				continue;
			}
			break;
		}

		data[child] = value;
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

template<typename T>
struct Stack {
	T * data;
	int size;
	int capasity;

	Stack(int init_capa = 2) :size(0), capasity(init_capa) {
		data = new T[init_capa];
	}

	~Stack() {
		delete[] data;
	}

	void resize(int new_capa) {
		T*new_data = new T[new_capa];
		for (int i = 0; i < size; ++i)
			new_data[i] = data[i];
		delete[] data;
		data = new_data;
		capasity = new_capa;
	}

	void clear() { size = 0; }

	void push(T value) {
		if (size == capasity) resize(capasity * 2);
		data[size++] = value;
	}

	T operator[](int index) {
		return data[index];
	}

};
struct Node {
	int node;
	int cost;

	bool operator<(const Node& other) {
		return cost < other.cost;
	}
};

Stack<Node> graph[50001];
Stack<Node> rev_graph[50001];
Heap<Node> heap;
int distance[50001][2];

int solve() {
	int n, m, x;
	std::cin >> n >> m >> x;

	for (int i = 1; i <= n; ++i) {
		distance[i][0] = INF;
		distance[i][1] = INF;
		graph[i].clear();
		rev_graph[i].clear();
	}

	while (m--) {
		int s, e, t;
		std::cin >> s >> e >> t;
		graph[s].push({ e, t });
		rev_graph[e].push({ s,t });
	}
	
	heap.clear();
	distance[x][0] = 0;
	heap.push({ x,0 });

	while (heap.size) {
		Node now = heap.pop();

		if (distance[now.node][0] < now.cost) continue;

		for (int i = 0; i < graph[now.node].size; ++i) {
			Node next = graph[now.node][i];

			if (distance[next.node][0] < now.cost + next.cost) continue;

			distance[next.node][0] = now.cost + next.cost;
			heap.push({ next.node, now.cost + next.cost });
		}
	}

	heap.clear();
	distance[x][1] = 0;
	heap.push({ x,0 });

	while (heap.size) {
		Node now = heap.pop();

		if (distance[now.node][1] < now.cost) continue;

		for (int i = 0; i < rev_graph[now.node].size; ++i) {
			Node next = rev_graph[now.node][i];

			if (distance[next.node][1] < now.cost + next.cost) continue;

			distance[next.node][1] = now.cost + next.cost;
			heap.push({ next.node, now.cost + next.cost });
		}
	}

	int answer = 0;

	for (int i = 1; i <= n; ++i) {
		if (distance[i][0] == INF || distance[i][1] == INF) continue;
		answer = answer > distance[i][0] + distance[i][1] ? answer : distance[i][0] + distance[i][1];
	}

	return answer;
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	freopen("간담회 참석_input.txt", "r", stdin);

	int T;
	std::cin >> T;
	for (int tc = 1; tc <= T; ++tc)
		std::cout << "#" << tc << " " << solve() << "\n";
}


#endif 