#if 0
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int node[262144];

unsigned int solve() {
	int n;
	std::cin >> n;

	for (int i = 0; i < 262144; ++i) node[i] = 0;

	unsigned int answer = 0;

	while (n--) {
		int temp; std::cin >> temp;
		int count = 0;

		int right = 100000;
		int left = 1;
		
		int index = 0;
		int mid = (left + right) >> 1;

		while (left < right) {
			if (mid <= temp) {
				left = mid + 1;
				count += node[(index << 1) + 1];
				index = (index << 1) + 2;
			}
			else {
				right = mid;
				index = (index << 1) + 1;
			}
			
			++node[index];
			mid = (left + right) >> 1;
		}

		answer += temp - 1 - count;
	}

	return answer;

}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	freopen("Inversion Counting_input.txt", "r", stdin);

	int T;
	std::cin >> T;
	for (int tc = 1; tc <= T; ++tc)
		std::cout << "#" << tc << " " << solve() << "\n";
}

#endif