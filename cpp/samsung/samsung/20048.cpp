#if 1

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

double dp[107][107];

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	std::cout.precision(15);
	freopen("input_20048.txt", "r", stdin);

	for (int i = 0; i < 106; i++) {
		dp[i+1][0] = (((dp[i][0] + 1) * 2) + (dp[i][0] * 4 * (i<<1))) / (((i << 1) + 1) * ((i << 1) + 2));
	}

	for (int i = 0; i < 106; i++) {
		for (int j = 0; j < 106; j++) {
			dp[i][j + 1] = ((dp[i][j] + 1) + (dp[i][j] * (2 * i + j))) / (2 * i + j + 1);
		}

	}

	int T, X, Y;
	std::cin >> T;
	for (int testcase = 1; testcase <= T; testcase++) {
		std::cin >> X >> Y;
		std::cout << "#" << testcase << " " << dp[X][Y] << "\n" ;
	}

}

#endif