#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <deque>
#include <vector>
#include <string>


const int dx[8] = { 0,1,0,-1,1,1,-1,-1 };
const int dy[8] = { 1,0,-1,0,1,-1,1,-1 };

int mine_map[300][300];
int ans, n;

bool is_zero(int x, int y)
{
	for (int dir = 0; dir < 8; dir++)
	{
		int nx = x + dx[dir];
		int ny = y + dy[dir];

		if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;

		if (mine_map[nx][ny] == -1) return false;
	}

	return true;
}

void click(int x, int y)
{
	// bfs를 위한 deque선언
	std::deque<std::pair<int, int>> visit;
	// 시작위치 deque에 넣고 해당 칸 처리
	visit.push_back({ x, y });
	mine_map[x][y] = 0;

	// deque가 빌때까지 bfs
	while (!visit.empty())
	{
		std::pair<int, int> now = visit[0];
		visit.pop_front();

		for (int dir = 0; dir < 8; dir++)
		{
			int nx = now.first + dx[dir];
			int ny = now.second + dy[dir];

			// 범위 벗어나거나 해당칸이 지뢰면 패스
			if (nx < 0 || nx >= n || ny < 0 || ny >= n || mine_map[nx][ny] != 1) continue;


			// 0인칸만 연쇄적으로 추가
			if (is_zero(nx, ny)) visit.push_back({ nx, ny });

			// 그냥 빈칸들은 방문처리 해줌
			mine_map[nx][ny] = 0;

		}

	}
}


void solve()
{
	//모든 좌표에 대해서
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			// 지뢰 위치는 패스
			if (mine_map[i][j] != 1) continue;

			// 0인 칸 먼저 클릭
			if (is_zero(i, j))
			{
				click(i, j);
				ans++;
			}
		}
	}

	//그 외에 남은 칸 클릭
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (mine_map[i][j] == 1) ans++;
}



int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	freopen("input_0610_4.txt", "r", stdin);

	int T;
	std::cin >> T;

	for (int test_case = 1; test_case <= T; test_case++)
	{
		ans = 0;
		std::cin >> n;


		for (int i = 0; i < n; i++)
		{
			std::string temp;
			std::cin >> temp;

			for (int j = 0; j < n; j++)
			{
				if (temp[j] == '.') mine_map[i][j] = 1;
				else mine_map[i][j] = -1;
			}

		}

		solve();
		std::cout << "#" << test_case << " " << ans << "\n";
	}

	return 0;
}
