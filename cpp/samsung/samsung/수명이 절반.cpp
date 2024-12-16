#if 0
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>

int N, K;
int W[200000], S[200000];
int memory[200000];

bool check(int a) {
	memory[0] = 1;
	memory[1] = 0;
	for (int i = 0; i < N; ++i) {
		if (a - W[i] >= 0) ++memory[memory[0]];
		else {
			// 0인 경우에는 해당값에 반영되므로 continue
			if (!memory[memory[0]]) continue;
			// 초기화
			memory[++memory[0]] = 0;
		}
	}

	int j = 1;
	for (int i = 0; i < K; ++i) {
		memory[j] -= S[i];
		while (memory[j] < 0) {
			if (++j > memory[0]) return false;
			memory[j] -= S[i];
		}
	}

	return true;
}

void solve(int tc) {
	std::cin >> N >> K;

	for (int i = 0; i < N; ++i)
		std::cin >> W[i];

	for (int i = 0; i < K; ++i)
		std::cin >> S[i];

	int left = 1, right = 200000;
	int mid;

	while (left < right) {
		mid = (left + right) >> 1;

		if (check(mid)) right = mid;
		else left = mid + 1;
	}

	std::cout << "#" << tc << " " << right << "\n";
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	freopen("수명이 절반.txt", "r", stdin);

	int T;
	std::cin >> T;

	for (int tc = 1; tc <= T; ++tc) 
		solve(tc);

}


#endif