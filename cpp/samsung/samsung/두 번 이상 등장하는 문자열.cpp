#if 0
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

char str[100000];
void solve(int tc) {
	int length;
	std::cin >> length;

	for (int i = 0; i < length; ++i)
		std::cin >> str[i];
	
}


int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	int T;
	std::cin >> T;
	for (int tc = 1; tc <= T; ++tc)
		solve(tc);
}


#endif