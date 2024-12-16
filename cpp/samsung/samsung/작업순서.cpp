#if 0
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int max(int a, int b) { return a > b ? a : b; }

struct Stack {
	int * data;
	int size;
	int capasity;

	Stack(int init = 2) :size(0), capasity(init) {
		data = new int[init];
	}
	~Stack() {
		delete[] data;
	}

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

	int operator[](int index) {
		return data[index];
	}

};

Stack turn[1001];
bool check[1001];
int time_[1001];
int V, E;
Stack answer[1001];

int cal_time(int task) {
	if (!turn[task].size) return 1;
	if (check[task]) return time_[task];

	int temp = 0;
	for (int i = 0; i < turn[task].size; ++i) {
		temp = max(temp, cal_time(turn[task][i]));
	}

	time_[task] = temp + 1;
	check[task] = true;

	return time_[task];
}


void solve() {
	std::cin >> V >> E;

	for (int i = 0; i <= V; ++i) {
		turn[i].clear();
		check[i] = false;
		answer[i].clear();
	}

	for (int i = 0; i < E; ++i) {
		int a, b;
		std::cin >> a >> b;
		turn[b].push(a);
	}

	for (int i = 1; i <= V; ++i) {
		time_[i] = cal_time(i);
		answer[time_[i]].push(i);
	}

	for (int i = 1; i <= V; ++i) {
		for (int j = 0; j < answer[i].size; ++j) {
			std::cout << answer[i][j] << " ";
		}
	}

	std::cout << "\n";

}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	freopen("작업순서_input.txt", "r", stdin);

	for (int tc = 1; tc <= 10; ++tc) {
		std::cout << "#" << tc << " ";
		solve();
	}
}



#endif 