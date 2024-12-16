#if 0
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>

long long pacto[21];

long long cal(int n, int left, int right, int count) {
	if (left + right == n - count) return pacto[left + right] / (pacto[left] * pacto[right]);
	if (!left && !right) return pacto[n-2] / pacto[count - 2];

	long long sum = 0;
	if (left) sum += cal(n, left - 1, right, count + 1);
	if (right) sum += cal(n, left, right - 1, count + 1);
	if (count >= 2) sum += cal(n, left, right, count + 1) * (count - 1);

	return sum;
}

long long solve() {
	int N, L, R;
	std::cin >> N >> L >> R;
	if (N == 1 && L == 1 && R == 1) return 1;
	if (L == 1 && R == 1) return 0;
	--L; --R;
	if (L + R >= N) return 0;

	return cal(N, L, R, 1);

}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	//freopen("pole_input.txt", "r", stdin);

	pacto[0] = 1;
	for (int i = 1; i <= 20; ++i) 
		pacto[i] = pacto[i-1] * i;

	int T;
	std::cin >> T;
	for (int tc = 1; tc <= T; ++tc)
		std::cout << "#" << tc << " " <<  solve() << "\n";
}
#endif

#if 0
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>

long long dp[21][21][21];

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	freopen("pole_input.txt", "r", stdin);

	dp[1][1][1] = 1;

	for (int n = 2; n <= 20; ++n) {
		for (int l = 1; l <= 20; ++l) {
			for (int r = 1; r <= 20; ++r) {
				dp[n][l][r] = dp[n - 1][l - 1][r]  // 맨 왼쪽에 추가
					+ dp[n - 1][l][r - 1]  // 맨 오른쪽에 추가
					+ dp[n - 1][l][r] * (n - 2); // 가운데 추가
			}
		}
	}

	int T;
	std::cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		int n, l, r;
		std::cin >> n >> l >> r;
		std::cout << "#" << tc << " " << dp[n][l][r] << "\n";
	}
}
#endif