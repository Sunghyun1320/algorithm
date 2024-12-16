#if 0
#define _CRT_SECURE_NO_WARNINGS
//#define min(x, y) (x) < (y) ? x:y
#define INF 987654321
#include <iostream>

int min(int a, int b) {
	if (a < b) return a;
	return b;
}

template<typename T>
struct Heap {
	T* data;
	int size;
	int capasity;

	Heap(int init_capasity = 2) : size(0), capasity(init_capasity) {
		data = new T[init_capasity];
	}

	~Heap() {
		delete[] data;
	}

	void clear() {
		size = 0;
	}

	void resize(int new_capasity) {
		T* new_data = new T[new_capasity];
		for (int i = 0; i < size; i++) {
			new_data[i] = data[i];
		}

		delete[] data;
		data = new_data;
		capasity = new_capasity;
	}


	void push(T value) {
		if (size == capasity) resize(capasity * 2);
		int child = size;

		while (child > 0) {
			int paridx = (child - 1) >> 1;
			T par = data[paridx];

			if (value < par) {
				data[child] = par;
				child = paridx;
				continue;
			}

			break;
		}

		data[child] = value;
		++size;
	}

	T pop() {
		if (size == 0) {
			//에러 출력
		}

		T return_value = data[0];
		T lastitem = data[--size];
		data[0] = lastitem;

		int paridx = 0;

		int child = 1;
		while (child < size) {
			int right = child + 1;
			if (right < size && !(data[child] < data[right])) child = right;

			if (data[child] < lastitem) {
				data[paridx] = data[child];
				paridx = child;
				child = (paridx << 1) + 1;
			}

			break;
		}
		data[paridx] = lastitem;
		return return_value;
	}
};

struct node {
	int now;
	int pathcount;
	int cost;

	node(int n = 0, int p = 0, int c = 0) :now(n), pathcount(p), cost(c) {}

	bool operator<(const node& other)const {
		if (cost == other.cost) return pathcount < other.pathcount;
		return cost < other.cost;
	}
};

template<typename T>
struct vector {
	T*data;
	int size;
	int capasity;

	vector(int init_capasity = 2): size(0), capasity(init_capasity) {
		data = new T[init_capasity];
	}

	~vector() {
		delete[] data;
	}

	void resize(int new_capasity) {
		T* new_data = new T[new_capasity];
		for (int i = 0; i < size; i++) {
			new_data[i] = data[i];
		}
		delete[] data;
		data = new_data;
		capasity = new_capasity;
	}

	void push(T value) {
		if (size == capasity) resize(capasity * 2);
		data[size++] = value;
	}

	T& operator[](int index) {
		if (index >= size) {
			//오류 출력
		}
		return data[index];
	}
};

int n, m, k, s, d;

int distance[1001][2];
int path_dis[1001][1001];
int path_cost[1001][1001];
vector<int> answer_path;
vector<int> graph[1001];
Heap<node> heap;

void dijk(int start, int goal) {
	for (int i = 0; i <= n; i++) {
		distance[i][0] = INF;
		distance[i][1] = INF;
		for (int j = 0; j <= n; j++) {
			path_dis[i][j] = INF;
		}
	}
	distance[start][0] = 0;
	distance[start][1] = 0;

	heap.push(node(start, 0, 0));

	while (heap.size) {
		node now = heap.pop();

		if (now.pathcount >= n) continue;
		if (distance[now.now][0] < now.cost &&
			distance[now.now][1] < now.pathcount) continue;

		for (int i = 0; i < graph[now.now].size; i++) {
			int next = graph[now.now][i];

			if (next == goal) {
				answer_path.push(now.cost + path_cost[now.now][next]);
				answer_path.push(now.pathcount + 1);
			}
			
			if (path_dis[next][now.pathcount + 1] < now.cost + path_cost[now.now][next]){
				continue;
			}

			heap.push(node(next, now.pathcount + 1, now.cost + path_cost[now.now][next]));
			
			path_dis[next][now.pathcount + 1] = now.cost + path_cost[now.now][next];
			if (distance[next][0] > now.cost + path_cost[now.now][next]) {
				distance[next][0] = now.cost + path_cost[now.now][next];
				distance[next][1] = now.pathcount + 1;
			}
		}

	}

}

int sum_tax, tax, answer;

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> n >> m >> k;
	std::cin >> s >> d;

	for (int i = 0; i <= n; i++) {
		for (int j = 0; j<= n; j++) {
			path_cost[i][j] = INF;
		}
	}

	while (m--) {
		int a, b, w;
		std::cin >> a >> b >> w;

		graph[a].push(b);
		graph[b].push(a);
		path_cost[a][b] = min(path_cost[a][b], w);
		path_cost[b][a] = min(path_cost[b][a], w);
	}

	dijk(s, d);
	
	for(int tc = 0; tc <= k; tc++){
		if (tc == 0) tax = 0;
		else std::cin >> tax;
		sum_tax += tax;

		answer = INF;
		for (int i = 0; i < answer_path.size >> 1 ; i++) {
			answer = min(answer, answer_path[i*2] + sum_tax * answer_path[i*2+1]);
		}

		std::cout << answer << "\n";
	}

}

#endif