#if 0

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

int T, X, Y;
double answer;

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	std::cout.precision(15);
	//freopen("input_20048.txt", "r", stdin);

	
	std::cin >> T;
	while (T--) {
		answer = 0;
		std::cin >> X >> Y;

		for (int i = 1; i <= X; i++)
			answer += (double)1 / (Y + 2 * i - 1);

		for (int i = 1; i <= Y; i++)
			answer += (double)1 / (i);

		std::cout << answer << "\n";


	}

}

#endif