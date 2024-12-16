#if 0

#include <iostream>

int* dp[251];

//값이 너무 크므로 1자리씩 계산
int* add(int* a, int* b) {
	// dp[250]이 100은 안넘겠지
	int* ans = new int[100];

	// 항상 a가 더 크다.
	if (a[0] < b[0]) {
		int* temp = a;
		a = b;
		b = a;
	}

	ans[0] = 0;
	int i = 1;
	while (i <= b[0]) {
		ans[i] = 0;
		ans[i] += ans[i - 1] / 10;
		ans[i - 1] %= 10;
		ans[i] += a[i];
		ans[i] += b[i];
		++i;
	}

	while (i <= a[0]) {
		ans[i] = 0;
		ans[i] += ans[i - 1] / 10;
		ans[i - 1] %= 10;
		ans[i] += a[i];
		++i;
	}

	if (ans[i - 1] / 10) {
		ans[i] = 0;
		ans[i] += ans[i - 1] / 10;
		ans[i - 1] %= 10;
		++i;
	}

	ans[0] = i - 1;

	return ans;
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	dp[0] = new int[100];
	dp[0][0] = 1;
	dp[0][1] = 1;
	dp[1] = new int[100];
	dp[1][0] = 1;
	dp[1][1] = 1;

	for (int i = 2; i <= 250; ++i)
		//dp[i] = (2 * dp[i-2]) + dp[i-1];
		dp[i] = add(add(dp[i - 2], dp[i - 2]), dp[i - 1]);

	int T; std::cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		int n; std::cin >> n;
		std::cout << "#" << tc << " ";
		for(int i = dp[n][0]; i>0; --i)
			std::cout << dp[n][i];
		std::cout << "\n";
	}
}


#endif