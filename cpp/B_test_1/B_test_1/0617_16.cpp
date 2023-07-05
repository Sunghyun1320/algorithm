#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>


int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	//freopen("input_0617_4.txt", "r", stdin);

	int T;
	std::cin >> T;

	for (int test_case = 1; test_case <= T; test_case++)
	{
		std::priority_queue<int> left, right;

		int N, a, b, ans;
		ans = 0;
		std::cin >> N >> a;

		left.push(a);

		for (int i = 0; i < N; i++)
		{
			std::cin >> a >> b;

			if (left.top() <= a) right.push(-a);
			else
			{
				int temp = left.top();
				left.pop();
				left.push(a);
				right.push(-temp);
			}


			if (left.top() > b) left.push(b);
			else if (-right.top() < b)
			{
				int temp = -right.top();
				right.pop();
				right.push(-b);
				left.push(temp);
			}
			else left.push(b);

			ans += left.top() % 20171109;
			ans %= 20171109;
		}

		std::cout << "#" << test_case << " " << ans << "\n";
	}





	return 0;
}