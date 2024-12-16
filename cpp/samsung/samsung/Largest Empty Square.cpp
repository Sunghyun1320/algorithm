#if 0
#include<iostream>

int min(int a, int b) { return a > b ? b : a; }
int max(int a, int b) { return a > b ? a : b; }

char map[1000][1000];
int dp[1001][1001];
int solve() {
	int n; std::cin >> n;
	for (int i = 0; i < n; ++i)std::cin >> map[i];

	int answer = 0;

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (map[i-1][j-1] == '1') {
				dp[i][j] = 0;
				continue;
			}

			dp[i][j] = min(dp[i-1][j-1], min(dp[i][j-1], dp[i-1][j])) + 1;
			answer = max(answer, dp[i][j]);
		}
	}

	return answer;

}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	int T; std::cin >> T;
	for (int tc = 1; tc <= T; ++tc)
		std::cout << "#" << tc << " " << solve() << "\n";
}

#endif