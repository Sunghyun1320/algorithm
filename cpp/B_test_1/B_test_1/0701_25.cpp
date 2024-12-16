#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

int binary_serach(long long n)
{
	long long left = 1, right = n / 2 + 1 < 1414213562 ? n / 2 + 1 : 1414213562;

	while (left < right)
	{
		long long mid = (left + right) / 2;

		long long a = (mid * mid + mid) / 2;
		long long b = (mid * mid + 3 * mid + 2) / 2;

		if (a < n && b < n)
			left = mid + 1;

		else if (a > n && b > n)
			right = mid;

		else if (a == n)
			return mid;

		else if (b == n)
			return mid + 1;

		else
			return -1;
	}

	return left;

}

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	freopen("input_0701_25.txt", "r", stdin);

	int T;

	std::cin >> T;

	for (int test_case = 1; test_case <= T; test_case++)
	{
		long long n;
		std::cin >> n;

		std::cout << "#" << test_case << " " << binary_serach(n) << "\n";
	}

	//long long n = 1414213500;
	//while (true)
	//{
	//	if ((n*n + n) / 2 > 1000000000000000000)
	//		break;
	//	std::cout << n << " : "<< (n*n + n) / 2 << "\n";
	//	n++;
	//}

	//std::cout << n << " : " << (n*n + n) / 2 << "\n";


	return 0;
}