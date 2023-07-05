#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>


int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	freopen("input_0617_3.txt", "r", stdin);

	int T;
	std::cin >> T;


	for (int test_case = 1; test_case <= T; test_case++)
	{

		int N;
		std::cin >> N;

		std::priority_queue<int> heap;

		std::cout << "#" << test_case << " ";

		for (int i = 0; i < N; i++)
		{
			int order;
			std::cin >> order;

			if (order == 1)
			{
				int value;
				std::cin >> value;
				heap.push(value);
			}
			else
			{
				int top = -1;
				if (!heap.empty()) {
					top = heap.top();
					heap.pop();
				}

				std::cout << top << " ";
			}
		}

		std::cout << "\n";
	}


	return 0;
}