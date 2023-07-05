#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

int n, max_core, min_elec_line;
int process_map[12][12];
std::vector<std::pair<int, int>> core;

const int dx[4] = { 0,1,0,-1 };
const int dy[4] = { 1,0,-1,0 };

int min(int a, int b)
{
	if (a > b) return b;
	return a;
}

int max(int a, int b)
{
	if (a > b) return a;
	return b;
}

void dfs(int core_num = 0, int core_cnt = 0, int elec_cnt = 0)
{

	if (core_num >= core.size())
	{
		if (max_core < core_cnt) {
			max_core = core_cnt;
			min_elec_line = elec_cnt;
		}

		if (max_core == core_cnt)
		{
			min_elec_line = min(elec_cnt, min_elec_line);
		}


		return;
	}

	//해당 코어를 연결하지 않는 경우
	dfs(core_num + 1, core_cnt, elec_cnt);
	
	std::pair<int, int>  temp = core[core_num];
	int x = temp.first;
	int y = temp.second;

	for (int dir = 0; dir < 4; dir++)
	{
		int nx = x + dx[dir];
		int ny = y + dy[dir];

		int new_elec_cnt = 0;

		while (true)
		{
			if (nx < 0 || nx >= n || ny < 0 || ny >= n)
			{
				dfs(core_num + 1, core_cnt + 1, elec_cnt + new_elec_cnt);
				break;
			}

			if (process_map[nx][ny] != 0)
				break;

			process_map[nx][ny] = -1;
			new_elec_cnt++;
			nx += dx[dir];
			ny += dy[dir];
		}

		while (true)
		{
			nx -= dx[dir];
			ny -= dy[dir];

			if (nx == x && ny == y) break;

			process_map[nx][ny] = 0;

		}
	}


	
}

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	freopen("input_0610_6.txt", "r", stdin);


	int T;
	std::cin >> T;

	for (int test_case = 1; test_case <= T; test_case++)
	{
		max_core = 0;
		min_elec_line = 0;
		core.clear();
		
		std::cin >> n;

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				int temp;
				std::cin >> temp;

				if (temp == 1 && i != 0 && i != n - 1 && j != 0 && j != n - 1)
				{
					core.push_back({ i, j });
				}

				process_map[i][j] = temp;

			}

		dfs();

		std::cout << "#" << test_case << " " << min_elec_line << "\n";

	}



	return 0;
}