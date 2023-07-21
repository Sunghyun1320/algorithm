#include <iostream>
#include <queue>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);

	int n;
	std::cin >> n;

	std::priority_queue<int> mirror[100001];
	std::vector<std::pair<int, int>> cat(n);

	//거울 위치 저장 후 고양이 순서를 거울 위로 저장
	//(1~100000 이므로 0부터 하기위해 고양이 위치를 거울위치로 바꿈)
	for (int i = 0; i < n; i++)
	{
		int x, y;
		std::cin >> x >> y;

		mirror[x].push(y);
		cat[i] = { x - 1, y };
	}

	std::vector<std::pair<int, bool>> kill_line[100001];

	for (int i = 0; i < 100001; i++)
	{
		kill_line[i].resize(mirror[i].size() + 2);
		kill_line[i][0] = { -1, false };

		int j = 1;

		while (!mirror[i].empty())
		{
			kill_line[i][j] = { mirror[i].top(), false };
			mirror[i].pop();
			j++;
		}

		kill_line[i][j] = { 100001,false };

	}

	int answer = 0;
	for (int i = 0; i < n; i++)
	{
		std::pair<int, int> attack = cat[i];

		for (int i = 0; i < kill_line[attack.first].size(); i++)
		{
			if (kill_line[attack.first][i].first > attack.second && !kill_line[attack.first][i - 1].second)
			{
				kill_line[attack.first][i - 1].second = true;
				answer++;
			}
		}
	}

	std::cout << answer;
	
	return 0;
}