#include <iostream>

int T;
int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);


	std::cin >> T;

	for (int test_case = 1; test_case <= T; test_case++)
	{
		int n, m;
		std::cin >> n >> m;
		bool answer = true;

		for (int i = 0; i < n; i++)
		{
			if (!(m & (1 << i)))
			{
				answer = false;
				break;
			}
		}

		if (answer) std::cout << "#" << test_case << " ON" << std::endl;
		else std::cout << "#" << test_case << " OFF" << std::endl;

	}



	return 0;
}