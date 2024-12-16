#if 0
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>

char charmap[8][8];
int n;

int solve() {
	std::cin >> n;
	if (n == 1) return 64;

	int answer = 0;

	for (int i = 0; i < 8; ++i) 
		for (int j = 0; j < 8; ++j) 
			std::cin >> charmap[i][j];

	bool check;

	//가로 체크
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8 - n + 1; ++j) {
			check = true;
			for (int k = 0; k < n >> 1; ++k) {
				if (charmap[i][j + k] != charmap[i][j + n - 1 - k]) {
					check = false;
					break;
				}
			}
			if (check) ++answer;
		}
	}

	//세로체크
	for (int j = 0; j < 8; ++j) {
		for (int i = 0; i < 8 - n + 1; ++i) {
			check = true;
			for (int k = 0; k < n >> 1; ++k) {
				if (charmap[i+k][j] != charmap[i + n - 1 - k][j]) {
					check = false;
					break;
				}
			}
			if (check) ++answer;
		}
	}


	return answer;
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	freopen("회문_input.txt", "r", stdin);

	for (int tc = 1; tc <= 10; ++tc)
		std::cout << "#" << tc << " " << solve() << "\n";
}
#endif