#if 1
#define _CRT_SECURE_NO_WARNINGS
#define INF 987654321

#include<iostream>

int min(int a, int b) { return a < b ? a : b; }

struct Node {
	int link;
	int cost;
	int dis;

	Node(int a=0, int b=0, int c=0):link(a), cost(b), dis(c){}

	bool operator<(const Node& other) {
		return dis < other.dis;
	}
};

struct Heap {
	Node data[10000];
	int size;

	void clear() { size = 0; }
	void push(Node value) {
		int child = size;

		while (child < size) {
			int paridx = (child - 1) >> 1;
			Node par = data[paridx];

			if (par < value) {
				data[child] = par;
				child = paridx;
				continue;
			}
			break;
		}

		data[child] = value;
		++size;
	}
	Node pop() {
		Node returnvalue = data[0];
		Node lastitem = data[--size];

		int par = 0;
		int child = 1;

		while(child < size) {
			int right = child + 1;
			if (right < size && !(data[child] < data[right])) child = right;

			if (data[child] < lastitem) {
				data[par] = data[child];
				par = child;
				child = (child << 1) + 1;
				continue;
			}
		}

		data[par] = lastitem;
		return returnvalue;
	}
}heap;

struct Queue {
	Node data[10000];
	int size;
	int start;

	void clear() {
		size = 0;
		start = 0;
	}
	void push(Node value) { data[(start + size++) % 10000] = value; }
	Node pop() { 
		--size;
		Node returnvalue = data[start];
		start = (start + 1) % 10000;
		return returnvalue; 
	}

};

struct stack {
	Node data[100];
	int size;

	void clear() { size = 0; }
	void push(Node value) { data[size++] = value; }
	Node pop() { return data[--size]; }
	Node operator[](int index) { return data[index]; }
} node[101];

int N, M, K;

int dis[101][101];

int distance[101];

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> N; // tc생략용 입력
	std::cin >> N >> M >> K;

	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j)
			dis[i][j] = INF;

	while (K--) {
		int u, v, c, d;
		std::cin >> u >> v >> c >> d;
		if (dis[u][v] == INF) {
			node[u].push(Node(v, c, d));
		}
		dis[u][v] = min(dis[u][v], d);
	}


	for (int i = 1; i <= N; ++i) distance[i] = INF;
	heap.clear();
	heap.push(Node(1, 0, 0));
	distance[1] = 0;

	while (heap.size) {
		Node now = heap.pop();

		if (now.link == N) break;

		for (int i = 0; i < node[now.link].size; ++i) {
			Node next = node[now.link][i];

			if (distance[next.link] < now.dis + dis[now.link][next.link]) continue;
			if (now.cost + next.cost > M) continue;

			distance[next.link] = now.dis + dis[now.link][next.link];
			next.dis = now.dis + dis[now.link][next.link];
			next.cost += now.cost;
			heap.push(next);
		}
	}

	if (distance[N] == INF) std::cout << "Poor KCM" << "\n";
	else std::cout << distance[N] << "\n";


}


#endif