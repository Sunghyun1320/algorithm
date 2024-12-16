#if 0
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>

int n;
int arr[10];
char tem[3];
char temp;

// 리터럴 \0때문에 4로 선언
const char num[10][4] = { "ZRO", "ONE", "TWO", "THR", "FOR", "FIV", "SIX", "SVN", "EGT", "NIN" };

void solve() {
	std::cin >> temp; //#생략용 입력
	std::cin >> n; // tc생략용 입력
	std::cin >> n;

	for (int i = 0; i < 10; ++i) arr[i] = 0;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 3; ++j) {
			std::cin >> tem[j];
		}

		if (tem[0] == 'Z')
			++arr[0];
		else if (tem[0] == 'O')
			++arr[1];
		else if (tem[0] == 'T' && tem[1] == 'W')
			++arr[2];
		else if (tem[0] == 'T' && tem[1] == 'H')
			++arr[3];
		else if (tem[0] == 'F' && tem[1] == 'O')
			++arr[4];
		else if (tem[0] == 'F' && tem[1] == 'I')
			++arr[5];
		else if (tem[0] == 'S' && tem[1] == 'I')
			++arr[6];
		else if (tem[0] == 'S' && tem[1] == 'V')
			++arr[7];
		else if (tem[0] == 'E')
			++arr[8];
		else if (tem[0] == 'N')
			++arr[9];

	}

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < arr[i]; ++j) {
			std::cout << num[i] << " ";
		}
	}

	std::cout << "\n";

}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	freopen("GNS_test_input.txt", "r", stdin);

	int T;
	std::cin >> T;

	for (int tc = 1; tc <= T; ++tc) {
		std::cout << "#" << tc << "\n";
		solve();
	}

}
#endif