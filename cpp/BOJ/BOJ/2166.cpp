#if 0
#include <iostream>

int n;

long double _abs(long double a) {
	if (a < 0) return -a;
	return a;
}

struct Pair {
	long long first;
	long long second;
};

Pair point[10001];


int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	std::cout.precision(1);

	std::cin >> n;
	for (int i = 0; i < n; i++)
		std::cin >> point[i].first >> point[i].second;

	point[n].first = point[0].first;
	point[n].second = point[0].second;


	long double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += point[i].first * point[i + 1].second;
		sum -= point[i + 1].first * point[i].second;
	}

	sum = _abs(sum);
	sum /= 2;

	std::cout << std::fixed << sum << "\n";
}


#endif