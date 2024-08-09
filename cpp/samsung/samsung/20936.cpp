#if 0
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

int N;
int arr[501];
bool check[501];
int answer[1500];
int count;
int target;

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	freopen("input_20936.txt", "r", stdin);

	int T;
	std::cin >> T;
	while (T--) {
		std::cin >> N;
		for (int i = 1; i <= N; i++) {
			int a;
			std::cin >> a;
			arr[a] = i;
			check[i] = false;
		}
		
		count = 0;
		for (int i = 1; i <= N; i++) {
			if (check[i]) continue;
			if (arr[i] == i) continue;
			check[i] = true;
			answer[count++] = i;
			target = arr[i];

			while (target != i) {
				answer[count++] = target;
				check[target] = true;
				target = arr[target];
			}

			answer[count++] = N + 1;
		}

		std::cout << count << "\n";
		for (int i = 0; i < count; i++) {
			std::cout << answer[i] << " ";
		}
		std::cout << "\n";
		

	}
}

#endif