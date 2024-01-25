#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>

int N, S;
int arr[100000];

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> N >> S;

	for (int i = 0; i < N; i++) {
		std::cin >> arr[i];
	}

	std::sort(std::begin(arr), std::begin(arr) + N);

	int i = 0;
	int j = 0;
	int answer = 0;
	int sum = arr[0];

	while(true) {
		if (i >= N || j > i) break;

		if (sum == S) {
			answer++;
			sum += arr[++i];
		}

		if (sum < S) sum += arr[++i];
		else sum -= arr[j++];
	}

	std::cout << answer << '\n';

	return 0;
}