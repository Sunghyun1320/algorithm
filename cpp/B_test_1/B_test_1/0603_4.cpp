#include <iostream>
#include <vector>

int T;

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> T;
	for (int test_case = 1; test_case <= T; test_case++)
	{
		int n, m, l;
		std::cin >> n >> m >> l;

		std::vector<int> arr;

		for (int i = 0; i < n; i++)
		{
			int temp;
			std::cin >> temp;
			arr.push_back(temp);
		}

		for (int i = 0; i < m; i++)
		{
			char order;
			std::cin >> order;
			if (order == 'I')
			{
				int index, value;
				std::cin >> index >> value;
				arr.insert(arr.begin() + index, 1, value);
			}

			else if (order == 'D')
			{
				int index;
				std::cin >> index;
				arr.erase(arr.begin() + index);
			}
			else if (order == 'C')
			{
				int index, value;
				std::cin >> index >> value;
				arr[index] = value;
			}

		}
		std::cout << "#" << test_case << " ";
		if (arr.size() < l)
			std::cout << -1 << '\n';
		else
			std::cout << arr[l] << '\n';




	}
}