#if 0
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

int T, n, m;
char data[50][101];
int code[245];

int solve_code(char chr[]) {
	int idx = 0;

	for (int i = 0; i < 7; i++) {
		if (chr[i]) idx = (idx << 1) + 1;
		else idx = (idx << 1) + 2;
	}

	return code[idx];
}

int solve() {

	std::cin >> n >> m;
	std::cin.get();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			std::cin.get(data[i][j]);
			data[i][j] -= '0';
		}
		std::cin.get();


	}

	int check = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (data[i][j] == 1) check = j;
		}

		if (!check) continue;

		check -= 55;

		int answer[8];

		for (int j = 0; j < 8; ++j) {
			answer[j] = solve_code(&data[i][check + j * 7]);
		}

		int temp1 = answer[0] + answer[2] + answer[4] + answer[6];
		int temp2 = answer[1] + answer[3] + answer[5] + answer[7];

		if ((temp1 * 3 + temp2) % 10) return 0;
		return temp1 + temp2;
	}
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	freopen("¾ÏÈ£_input.txt", "r", stdin);

	code[241] = 0;
	code[229] = 1;
	code[235] = 2;
	code[193] = 3;
	code[219] = 4;
	code[205] = 5;
	code[207] = 6;
	code[195] = 7;
	code[199] = 8;
	code[243] = 9;

	std::cin >> T;
	for (int tc = 1; tc <= T; ++tc)
		std::cout<< "#" << tc << " " << solve() << "\n";

}

#endif