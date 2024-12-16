//#pragma warning(disable:4996)
#include <iostream>

using namespace std;

int n;
double per[4];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

bool visited[29][29] = { false };

double answer = 0.0;

void back(int x, int y, double percent, int depth, int n) 
{
	if (percent == 0) return;

	if (depth == n)
	{
		answer += percent;
		return;
	}

	for (int dir = 0; dir < 4; dir++)
	{
		int nx = x + dx[dir];
		int ny = y + dy[dir];

		if (visited[nx][ny]) continue;

		visited[nx][ny] = true;
		back(nx, ny, percent * per[dir], depth + 1, n);
		visited[nx][ny] = false;
	}

	return;
}

int main()
{
	// n 입력받기
	cin >> n;

	//4가지 방향에 대한 확률 입력받기
	for (int i = 0; i < 4; i++)
	{
		int a;
		cin >> a;
		per[i] = a / 100.0;
	}

	visited[14][14] = true;

	back(14, 14, 1, 0, n);

	cout.precision(15);
	cout << fixed << answer;

}