#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

bool compare(int a, int b)
{
	if (a > 100001) a -= 100001;
	if (b > 100001) b -= 100001;

	return a < b;
}

int n;
std::vector<int> mirror[100001];
int answer = 0;

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);

	std::cin >> n;


	//거울 위치 저장 후 고양이 순서를 거울 위로 저장
	//(1~100000 이므로 0부터 하기위해 고양이 위치를 거울위치로 바꿈)
	for (int i = 0; i < n; i++)
	{
		int x, y;
		std::cin >> x >> y;

		mirror[x].push_back(y);
		mirror[x - 1].push_back(100001 + y);
	}


	for (int i = 0; i < 100000; i++)
	{
		std::sort(mirror[i].begin(), mirror[i].end(), compare);
		bool check = true;
		for (int j = 0; j < mirror[i].size(); j++)
		{
			if (mirror[i][j] > 100000 && check)
			{
				check = false;
				answer++;
			}

			if (mirror[i][j] <= 100000)
				check = true;
		}
	}

	std::cout << answer;
	
	return 0;
}