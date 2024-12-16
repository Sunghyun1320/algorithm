#if 0
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>

int n;

struct Magnetic {
	int point;
	int mess;

	double pullforce(double x) {
		return (double)mess / (((double)point - x) * ((double)point - x));
	}
}ma[10];



void solve() {
	std::cin >> n;
	for (int i = 0; i < n; ++i) std::cin >> ma[i].point;
	for (int i = 0; i < n; ++i) std::cin >> ma[i].mess;

	double left;
	double right;
	double mid;
	double force;
	for (int i = 0; i < n - 1; ++i) {
		left = ma[i].point;
		right = ma[i + 1].point;

		while (left < right) {
			mid = (left + right) / 2;
			force = 0;

			for (int j = 0; j < n; ++j) {
				if (j <= i) force += ma[j].pullforce(mid);
				else force -= ma[j].pullforce(mid);
			}

			if (force < 0) right = mid - 1e-12;
			else if(force > 0) left = mid + 1e-12;
			else { left = mid; break; }
		}

		std::cout << left << " ";
	}

	std::cout << "\n";

}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	freopen("±ÕÇüÁ¡_input.txt","r",stdin);

	std::cout.precision(10);
	std::cout << std::fixed;

	int T;
	std::cin >> T;
	for (int tc = 1; tc <= T; ++tc) {
		std::cout << "#" << tc << " ";
		solve();
	}

}



#endif