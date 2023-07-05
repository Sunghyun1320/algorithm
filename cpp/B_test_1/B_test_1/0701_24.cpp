#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

int n, p;
int study_day[200001];
int between[200001];

int max(int a, int b)
{
	return a > b ? a : b;
}


int solve()
{
	std::cin >> n >> p;

	std::cin >> study_day[0];
	between[0] = 0;

	for (int i = 1; i < n; i++)
	{
		std::cin >> study_day[i];
		between[i] = study_day[i] - study_day[i - 1] - 1;
	}

	int a = 0, b = 0, sum = 0, answer = p + 1;

	while (b < n)
	{

		if (sum <= p)
			sum += between[++b];

		else
		{
			if (a == b)
				sum += between[++b];

			else
			{
				answer = max(answer, study_day[b - 1] - study_day[a] + 1 + (p - (sum - between[b])));
				sum -= between[++a];
			}
		}

	}

	answer = max(answer, study_day[b - 1] - study_day[a] + 1 + (p - (sum - between[b])));
	return answer;
}


int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	freopen("input_0710_24.txt", "r", stdin);

	int T;

	std::cin >> T;

	for (int test_case = 1; test_case <= T; test_case++)
		std::cout << "#" << test_case << " " << solve() << "\n";


	return 0;
}