#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

int N, K, v, c;

int dp[101][1001] = { 0 };

int max(int a, int b)
{
	if (a > b) return a;
	return b;
}


int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	freopen("input_0617_2.txt", "r", stdin);

	int T;
	std::cin >> T;

	for (int test_case = 1; test_case <= T; test_case++)
	{
		std::cin >> N >> K;

		for (int i = 1; i <= N; i++)
		{
			std::cin >> v >> c;

			for (int j = 1; j < v; j++)
			{
				dp[i][j] = dp[i - 1][j];
			}

			for (int j = v; j <= K; j++)
			{
				dp[i][j] = max(dp[i - 1][j - v] + c, dp[i - 1][j]);
			}
		}

		std::cout << "#" << test_case << " " << dp[N][K] << "\n";
	}


	return 0;
}