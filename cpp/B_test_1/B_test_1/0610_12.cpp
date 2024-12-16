#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 1
#define CMD_NUMBER_OF_CANDIDATE 2
#define CMD_MAX_AREA 3

extern void init(int N, int mMap[20][20]);
extern int numberOfCandidate(int M, int mStructure[5]);
extern int maxArea(int M, int mStructure[5], int mSeaLevel);

/////////////////////////////////////////////////////////////////////////

#include <deque>

const int dx[4] = { 0,1,0,-1 };
const int dy[4] = { 1,0,-1,0 };

int map[22][22];
int n;
int data[55556] = { 0 };

void init(int N, int mMap[20][20])
{
	for (int i = 0; i < 55556; i++)
		data[i] = 0;

	n = N;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int hash = 0;
			for (int k = 0; k < 5; k++)
			{
				if (j + k >= N) break;

				hash = hash * 10 + mMap[i][j + k];
				data[hash] += 1;
			}

			hash = mMap[i][j];
			for (int k = 1; k < 5; k++)
			{
				if (i + k >= N) break;

				hash = hash * 10 + mMap[i + k][j];
				data[hash] += 1;
			}
		}
	}

	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 22; j++)
		{
			map[i][j] = 0;
		}
	}


	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			map[i + 1][j + 1] = mMap[i][j];
		}
	}

}

int numberOfCandidate(int M, int mStructure[5])
{
	if (M == 1) return n * n;

	int answer = 0;
	bool is_reverse_same = true;

	for (int i = 1; i <= 5; i++)
	{
		int goal_h = i + mStructure[0];

		int hash = i;

		bool check = true;
		for (int j = 1; j < M; j++)
		{
			if (goal_h - mStructure[j] <= 0 || goal_h - mStructure[j] > 5)
			{
				check = false;
				break;
			}
			hash = hash * 10 + (goal_h - mStructure[j]);
		}
		if (check)
			answer += data[hash];
	}

	for (int i = 0; i < int(M / 2); i++)
	{
		if (mStructure[i] != mStructure[M - i - 1]) is_reverse_same = false;
	}

	if (is_reverse_same) return answer;

	for (int i = 1; i <= 5; i++)
	{
		int goal_h = i + mStructure[M-1];

		int hash = i;

		bool check = true;
		for (int j = M-2; j >= 0; j--)
		{
			if (goal_h - mStructure[j] <= 0 || goal_h - mStructure[j] > 5)
			{
				check = false;
				break;
			}
			hash = hash * 10 + (goal_h - mStructure[j]);
		}
		if (check)
			answer += data[hash];
	}
	return answer;
}

int bfs(int mSeaLevel, int min_answer)
{

	int answer = 0;

	std::deque<std::pair<int, int>> visit;
	bool visited[22][22] = { false };
	visit.push_back({ 0, 0 });
	visited[0][0] = true;
	answer++;

	while (!visit.empty())
	{
		std::pair<int, int> now = visit[0];
		visit.pop_front();

		for (int dir = 0; dir < 4; dir++)
		{
			int nx = now.first + dx[dir];
			int ny = now.second + dy[dir];

			if (visited[nx][ny]) continue;

			if (map[nx][ny] < mSeaLevel)
			{
				visit.push_back({ nx, ny });
				visited[nx][ny] = true;
				answer++;
				if (answer >= min_answer) return answer;
			}
		}
	}


}


int maxArea(int M, int mStructure[5], int mSeaLevel)
{
	if (numberOfCandidate(M, mStructure) == 0) return -1;



}
/////////////////////////////////////////////////////////////////////////

static int mMap[20][20];
static int mStructure[5];

static bool run()
{
	int numQuery;
	int N, M, mSeaLevel;
	int userAns, ans;

	bool isCorrect = false;

	scanf("%d", &numQuery);

	for (int i = 0; i < numQuery; ++i)
	{
		int cmd;
		scanf("%d", &cmd);

		switch (cmd)
		{
		case CMD_INIT:
			scanf("%d", &N);
			for (int j = 0; j < N; j++)
				for (int k = 0; k < N; k++)
					scanf("%d", &mMap[j][k]);
			init(N, mMap);
			isCorrect = true;

			break;

		case CMD_NUMBER_OF_CANDIDATE:
			scanf("%d", &M);
			for (int j = 0; j < M; j++)
				scanf("%d", &mStructure[j]);
			userAns = numberOfCandidate(M, mStructure);
			scanf("%d", &ans);
			if (userAns != ans)
			{
				isCorrect = false;
			}
			break;

		case CMD_MAX_AREA:
			scanf("%d", &M);
			for (int j = 0; j < M; j++)
				scanf("%d", &mStructure[j]);
			scanf("%d", &mSeaLevel);
			userAns = maxArea(M, mStructure, mSeaLevel);
			scanf("%d", &ans);
			if (userAns != ans)
			{
				isCorrect = false;
			}
			break;

		default:
			isCorrect = false;
			break;
		}
	}
	return isCorrect;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("input_0610_7.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}