#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>


int dp[1001][1001] = { 0 };

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

	freopen("input_0617_1.txt", "r", stdin);

	int T;
	std::cin >> T;

	for (int test_case = 1; test_case <= T; test_case++)
	{
		std::string a, b;
		std::cin >> a >> b;

		for (int i = 0; i < a.length(); i++)
		{
			for (int j = 0; j < b.length(); j++)
			{
				if (a[i] == b[j]) 
					dp[i + 1][j + 1] = dp[i][j] + 1;
				else 
					dp[i + 1][j + 1] = max(dp[i][j+1], dp[i + 1][j]);
			}
		}


		std::cout << "#" << test_case << " " << dp[a.length()][b.length()] << "\n";
	}


	return 0;
}