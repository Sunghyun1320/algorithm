#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

int n;
long long m;
long long candy[100];

int solve()
{
	std::cin >> n >> m;

	for (int i = 0; i < n; i++)
		std::cin >> candy[i];



	return 0;
}

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	freopen("input_0701_26.txt", "r", stdin);

	int T;
	std::cin >> T;

	for (int test_case = 1; test_case <= T; test_case++)
		std::cout << "#" << test_case << " " << solve() << "\n";



	return 0;
}