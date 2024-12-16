#if 0
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>

int N;
char graph[100][100];

int solve() {
	std::cin >> N;

	for (int i = 0; i < N; ++i) 
		for (int j = 0; j < N; ++j) {
			std::cin >> graph[i][j];
			graph[i][j] -= '0';
		}

	int answer = 0;

	for (int j = 0; j < N; ++j) {
		bool check = false;
		for (int i = 0; i < N; ++i) {
			if (!graph[i][j]) continue;

			if (graph[i][j] == 1 && !check) check = true;
			else if (graph[i][j] == 2 && check) {
				++answer;
				check = false;
			}

		}
	}

	return answer;
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	freopen("magnetic_test_input.txt","r",stdin);

	int T;
	//std::cin >> T;
	T = 10;
	for (int tc = 1; tc <= T; ++tc) {
		std::cout << "#" << tc << " " << solve() << "\n";
	}
}


#endif