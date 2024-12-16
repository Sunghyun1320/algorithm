#if 0
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

long long solve() {
	int n, p;
	std::cin >> n >> p;

	long long answer = 1LL;
	for (int i = 0; i < p; ++i) {
		if (i < n%p) answer *= (n / p + 1);
		else answer *= n / p;
	}

	return answer;
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	//freopen("", "r", stdin);

	int T;
	std::cin >> T;
	for (int tc = 1; tc <= T; ++tc)
		std::cout << "#" << tc << " " << solve() << "\n";

}

#endif