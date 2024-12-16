#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <deque>
#include <vector>

int n;
int parents[100001][17];
int level[100001];
bool visited[100001];
std::vector<int> tree[100001];


int LCA(int x, int y)
{
	int cnt = 0;

	if (level[x] > level[y])
	{
		int temp = x;
		x = y;
		y = temp;

	}

	if (parents[y][0] == x) return 1;

	for (int i = 16; i >= 0; i--)
	{
		if (level[y] - level[x] >= (1 << i))
		{
			y = parents[y][i];
			cnt += (1 << i);
		}
	}

	if (parents[y][0] != parents[x][0])
	{
		for (int i = 16; i >= 0; i--)
		{
			if (parents[x][i] != parents[y][i])
			{
				x = parents[x][i];
				y = parents[y][i];
				cnt += 2 * (1 << i);
			}
		}
	}

	if (parents[x][0] == parents[y][0]) return cnt + 2;


	return 0;
}


int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	freopen("input_0610_5.txt", "r", stdin);

	int T;
	std::cin >> T;

	for (int test_case = 1; test_case <= T; test_case++)
	{
		for (int i = 0; i < 100001; i++)
		{
			tree[i].clear();
			level[i] = 0;
			visited[i] = false;
		}


		std::cin >> n;

		for (int i = 2; i <= n; i++)
		{
			int par;
			std::cin >> par;
			parents[i][0] = par;
			level[i] = level[par] + 1;
			tree[par].push_back(i);
		}

		for (int i = 1; i < 17; i++)
			for (int j = 1; j <= n; j++)
				parents[j][i] = parents[parents[j][i - 1]][i - 1];




		long long int answer = 0;
		int before;
		std::deque<int> visit;
		visit.push_back(1);
		visited[1] = true;
		before = 1;
		while (!visit.empty())
		{
			int now = visit[0];
			visit.pop_front();
			for (int i = 0; i < tree[now].size(); i++)
			{
				int next = tree[now][i];
				
				if (visited[next]) continue;

				visit.push_back(next);
				visited[next] = true;
				answer += LCA(before, next);
				before = next;
			}
		}

		std::cout << "#" << test_case << " " << answer << "\n";
	}





	return 0;
}