#if 0
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>

int Combination(int r, int n = 18) {
	if (r > n) return 0;
	if (r == 0 || r == n) return 1;

	if (r > n - r) r = n - r;

	int answer = 1;

	for (int i = 0; i < r; ++i) {
		answer *= (n - i);
		answer /= (i + 1);
	}

	return answer;

}

double cal(int a, double p) {
	double per = (double)Combination(a);

	for (int i = 0; i < a; ++i) {
		per *= p;
	}

	for (int i = 0; i < 18 - a; ++i) {
		per *= (1 - p);
	}

	return per;
	
}


const int non_prime[12] = {0,1,4,6,8,9,10,12,14,15,16,18 };
int T;
double A_master, B_master;
double solve() {
	std::cin >> A_master >> B_master;

	A_master /= 100.0;
	B_master /= 100.0;

	double a_p = 0.0;
	double b_p = 0.0;

	for (int i = 0; i < 12; ++i) {
		a_p += cal(non_prime[i], A_master);
		b_p += cal(non_prime[i], B_master);
	}

	int returnvalue = (int)((1 - (a_p * b_p)) * 10000000);
	returnvalue += 5;
	returnvalue /= 10;

	return returnvalue / 1000000.0;
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	freopen("소수완제품확률.txt", "r", stdin);

	std::cout.precision(6);
	std::cout << std::fixed;

	std::cin >> T;

	for (int tc = 1; tc <= T; ++tc) {
		std::cout <<  "#" << tc << " " << solve() << "\n";
	}

}


#endif