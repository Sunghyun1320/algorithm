#if 0
#define _CRT_SECURE_NO_WARNINGS

#define MAX_DEPTH 10000
#define LOG 15
#include<iostream>

struct Stack {
	int* data;
	int size;
	int capasity;

	Stack(int init = 2) : size(0), capasity(init) {
		data = new int[init];
	}

	~Stack() { delete[] data; }

	void resize(int new_capa) {
		int* new_data = new int[new_capa];
		for (int i = 0; i < size; ++i) 
			new_data[i] = data[i];

		delete[] data;
		data = new_data;
		capasity = new_capa;
	}
	void clear() { size = 0; }
	void push(int value) {
		if (size == capasity) resize(capasity * 2);
		data[size++] = value;

	}
	int pop() { return data[--size]; }
	int operator[](int index) { return data[index]; }
};

Stack graph[MAX_DEPTH + 1];
int tree[MAX_DEPTH + 1][LOG];
int level[MAX_DEPTH + 1];


//레벨 찾는 함수와 서브노드 찾는 함수를 같이 사용
//dfs를 2번하므로 비효율...
//비효율인줄 알았더니 재귀보다 빠르네
int check_level(int root = 1) {
	Stack dfs;
	dfs.push(root);
	level[root] = 0;
	int count = 0;

	while (dfs.size) {
		int now = dfs.pop();
		++count;

		for (int i = 0; i < graph[now].size; ++i) {
			int next = graph[now][i];

			level[next] = level[now] + 1;
			tree[next][0] = now;
			dfs.push(next);
		}
	}

	return count;
}


/*
//dfs한번 하는데... 왜 더 느림?
//재귀호출이라서 좀 더 느린가....
int count_sub[MAX_DEPTH + 1];
int check_level(int now = 1, int now_level = 0) {

	int count = 1;

	for (int i = 0; i < graph[now].size; ++i) {
		int next = graph[now][i];
		tree[next][0] = now;
		count += check_level(next, now_level+1);
	}

	count_sub[now] = count;
	level[now] = now_level;
	return count;

}
*/
void solve() {
	int V, E, a, b;
	std::cin >> V >> E >> a >> b;

	for (int i = 1; i <= V; ++i) 
		graph[i].clear();
	
	for (int i = 0; i < E; ++i) {
		int c, d;
		std::cin >> c >> d;
		graph[c].push(d);
	}

	check_level();

	for (int j = 1; j < LOG; ++j) 
		for (int i = 1; i <= V; ++i) 
			tree[i][j] = tree[tree[i][j - 1]][j - 1];
		
	if (level[a] < level[b]) {
		int temp = a;
		a = b; b = temp;
	}
	
	for (int i = LOG - 1; i >= 0; --i) 
		if (level[a] - level[b] >= 1 << i) a = tree[a][i];
	
	if (a == b) {
		std::cout << a << " " << check_level(a) << "\n";
		//std::cout << a << " " << count_sub[a] << "\n";
		return;
	}

	for (int i = LOG - 1; i >= 0; --i)
		if (tree[a][i] != tree[b][i]) {
			a = tree[a][i];
			b = tree[b][i];
		}

	std::cout << tree[a][0] << " " << check_level(tree[a][0]) << "\n";
	//std::cout << tree[a][0] << " " << count_sub[tree[a][0]] << "\n";

};

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0), std::cout.tie(0);
	freopen("LCA_input.txt","r",stdin);

	int T;
	std::cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		std::cout << "#" << tc << " ";
		solve();
	}

}
#endif