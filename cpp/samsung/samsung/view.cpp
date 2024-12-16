#if 0
#define _CRT_SECURE_NO_WARNINGS
//#define max(a,b)(a)>(b)?(a):(b)
#include <iostream>

int max(int a, int b) {
	if (a > b)return a;
	return b;
}

int T, n;
int buliding[1000];

int solve() {
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		std::cin >> buliding[i];
	}

	int answer = 0;
	for (int i = 2; i < n - 2; ++i) {
		int temp = -1;
		for (int j = -2; j < 3; ++j) {
			if (j == 0) continue;

			temp = max(temp, buliding[i + j]);
		}
		answer += max(0, buliding[i] - temp);
	}

	return answer;
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	freopen("view_test_input.txt","r",stdin);

	std::cin >> T;

	for (int tc = 1; tc <= T; ++tc) {
		std::cout << '#' << tc << ' ' << solve() << '\n';
	}
}


#endif