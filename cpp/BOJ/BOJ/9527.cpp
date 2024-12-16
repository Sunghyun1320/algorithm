#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

long long a, b;

// a까지의 1의 개수 합을 구하는 함수
// x = a * 2^n + b * 2^n-1 + c
// f(x) = a * 2^n-1 + b*c
long long countsumone(long long a) {
	//자리수
	int i = 1;
	//반환값
	long long sum = 0;
	//나머지
	long long rest = 0;
	while (a) {
		rest |= (a & 1LL) << (i-1);
		// 몫 만큼 더함
		sum += (a >> 1) * (1LL << (i - 1));
		// 나머지 처리
		sum += (rest >> (i-1)) * (rest - (1LL << (i - 1)));
		a = a >> 1;
		i++;

	}

	return sum;
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> a >> b;

	std::cout << countsumone(b+1) - countsumone(a) << "\n";


	return 0;
}