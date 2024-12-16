#if 0
#include<iostream>
int max(int a, int b) { return a > b ? a : b; }

char A[1001], B[1001];
int dp[1001][1001];

int solve() {
	std::cin >> A;
	std::cin >> B;

	int i = 0, j = 0;
	int answer = 0;
	while (true) {
		j = 0;
		while (true) {
			if (i == 0 || j == 0)
				dp[i][j] = 0;
			else if (A[i-1] == B[j-1])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

			answer = max(answer, dp[i][j]);

			if (B[j++] == '\0') break;
		}
		if (A[i++] == '\0') break;
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