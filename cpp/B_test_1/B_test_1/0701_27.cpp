#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

int L, N;
std::vector<std::pair<int, int>> pick_time(100000);
int empty_time[100000];

int max(int a, int b)
{
	return a > b ? a : b;
}

int solve()
{

	std::cin >> L >> N;

	int answer = 0;
	std::cin >> pick_time[0].first >> pick_time[0].second;
	empty_time[0] = 0;

	for (int i = 1; i < N; i++)
	{
		std::cin >> pick_time[i].first >> pick_time[i].second;
		empty_time[i] = empty_time[i - 1] + pick_time[i].first - pick_time[i - 1].second;
	}

	if (pick_time[N - 1].second - pick_time[0].first <= L)
		return pick_time[N - 1].second - pick_time[0].first - empty_time[N - 1];

	for (int i = 0; i < N; i++)
	{
		int left = i, right = N;
		int end_time = pick_time[i].first + L;

		while (left < right)
		{
			int mid = (left + right) / 2;

			if(mid == N - 1)
			{
				answer = max(answer, pick_time[mid].second - pick_time[i].first - (empty_time[mid] - empty_time[i]));
				break;
			}


			if (pick_time[mid].first < end_time && end_time <= pick_time[mid].second)
			{
				answer = max(answer, L - (empty_time[mid] - empty_time[i]));
				break;
			}

			else if (pick_time[mid].second < end_time)
				if (pick_time[mid + 1].first >= end_time)
				{
					answer = max(answer, pick_time[mid].second - pick_time[i].first - (empty_time[mid] - empty_time[i]));
					break;
				}
				else
					left = mid + 1;

			else if (pick_time[mid].first >= end_time)
				right = mid;

		}
	}

	return answer;
}




int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	freopen("input_0701_27.txt", "r", stdin);

	int T;

	std::cin >> T;

	for (int test_case = 1; test_case <= T; test_case++)
		std::cout << "#" << test_case << " " << solve() << "\n";


	return 0;
}