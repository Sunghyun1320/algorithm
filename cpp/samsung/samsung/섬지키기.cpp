#if 0
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
int max(int a, int b) {
	if (a > b) return a;
	return b;
}

template<typename T>
struct Stack{
	T* data;
	int size;
	int capasity;

	Stack(int init_capa = 2) : size(0), capasity(init_capa) {
		data = new T[init_capa];
	}

	~Stack() {
		delete[] data;
	}

	void clear() { size = 0; }

	void resize(int new_capa) {
		T* new_data = new T[new_capa];
		for (int i = 0; i < size; ++i) {
			new_data[i] = data[i];
		}
		delete[] data;
		data = new_data;
		capasity = new_capa;
	}

	void push(T value) {
		if (size == capasity) resize(capasity * 2);

		data[size++] = value;
	}

	T& operator[](int index) {
		if(index >= size) {/*error*/ }
		return data[index];
	}

};

template<typename T>
struct Queue {
	T* data;
	int start;
	int size;
	int capasity;

	Queue(int init_capa = 2) :start(0), size(0), capasity(init_capa) {
		data = new T[init_capa];
	}

	~Queue() {
		delete[] data;
	}

	void clear() {
		start = 0;
		size = 0;
	}

	void resize(int new_capa) {
		T* new_data = new T[new_capa];
		for (int i = 0; i < size; ++i) {
			new_data[i] = data[(start + i) % capasity];
		}
		start = 0;
		delete[] data;
		data = new_data;
		capasity = new_capa;
	}

	void push(T value) {
		if (size == capasity) resize(capasity * 2);
		data[(start + size++) % capasity] = value;
	}

	T pop() {
		if(size == 0) {/*error*/ }
		--size;

		T returnvalue = data[start];
		start = (start + 1) % capasity;
		return returnvalue;
	}

	T& operator[](int index) {
		if(index >= size) {/*error*/ }
		return data[(start + index) % capasity];
	}
};

const int dx[4] = { 0,1,0,-1 };
const int dy[4] = { 1,0,-1,0 };

// 기본 맵을 해시로 저장하여 시작위치와 수직여부, 반전 여부를 저장
struct hashnode {
	int x;
	int y;
	bool isHoriz;
	bool isReverse;

	hashnode(int a=0, int b=0, bool c=false, bool d=false): x(a), y(b), isHoriz(c), isReverse(d){}
};

struct bfsnode {
	int x;
	int y;

	bfsnode(int a=0, int b=0): x(a), y(b){}
};


//맵의 구조에 따라 해시로 값을 저장
//구조물의 최대 길이가 5이므로 해시는 최대 4자리 정수
Stack<hashnode> hashmap[10000];
int n;

//기본제공 그래프와 구조물을 생성할 그래프를 분리
int graph[22][22], tempgraph[22][22];

//bfs용 변수
bool check[22][22];
Queue<bfsnode> bfs;

void init(int N, int mMap[20][20])
{
	n = N;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			graph[i+1][j+1] = mMap[i][j];
			tempgraph[i+1][j+1] = mMap[i][j];
		}
	}

	for (int i = 0; i < 10000; ++i) hashmap[i].clear();

	for (int len = 2; len <= 5; ++len) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j + len - 1 <= n; ++j) {

				//i,j를 기준으로 오른쪽 len길이 만큼의 hash를 측정
				//방향은 오른쪽 방향
				int hash = 0;
				for (int k = 0; k + 1 < len; ++k) {
					hash = hash * 10 + (graph[i][j + k + 1] - graph[i][j + k] + 5);
				}
				hashmap[hash].push(hashnode(i, j, true, false));

				//i,j를 기준으로 오른쪽 len길이 만큼의 hash를 측정
				//방향은 왼쪽 방향
				int reversehash = 0;
				for (int k = len - 1; k - 1 >= 0; --k) {
					reversehash = reversehash * 10 + (graph[i][j + k - 1] - graph[i][j + k] + 5);
				}
				//같은 값일 경우 추가 안 함
				if (reversehash != hash)
					hashmap[reversehash].push(hashnode(i, j, true, true));

			}
		}

		for (int i = 1; i + len - 1 <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				//i,j를 기준으로 아래방향 len길이 만큼의 hash를 측정
				//방향은 아래 방향
				int hash = 0;
				for (int k = 0; k + 1 < len; ++k) {
					hash = hash * 10 + (graph[i + k + 1][j] - graph[i + k][j] + 5);
				}
				hashmap[hash].push(hashnode(i, j, false, false));

				// i,j를 기준으로 아래방향 len길이 만큼의 hash를 측정
				// 방향은 윗 방향
				int reversehash = 0;
				for (int k = len - 1; k - 1 >= 0; --k) {
					reversehash = reversehash * 10 + (graph[i + k - 1][j] - graph[i + k][j] + 5);
				}
				if (reversehash != hash)
					hashmap[reversehash].push(hashnode(i, j, false, true));
			}
		}
	}
}

int numberOfCandidate(int M, int mStructure[5])
{
	if (M == 1) return n * n;

	int hash = 0;
	for (int i = 0; i + 1 < M; ++i) {
		hash = hash * 10 + (mStructure[i] - mStructure[i + 1] + 5);
	}
	return hashmap[hash].size;
}

int checkArea(int graph_t[22][22], int sealevel)
{
	// 기본 변수 초기화
	bfs.clear();
	for (int i = 0; i <= n + 1; ++i) {
		for (int j = 0; j <= n + 1; ++j) {
			check[i][j] = false;
		}
	}

	//bfs시작
	for (int i = 0; i <= n+1; ++i) {
		bfs.push(bfsnode(0, i));
		bfs.push(bfsnode(i, 0));
		bfs.push(bfsnode(n + 1, i));
		bfs.push(bfsnode(i, n + 1));
		check[0][i] = true;
		check[i][0] = true;
		check[n + 1][0] = true;
		check[0][n + 1] = true;
	}

	while (bfs.size) {
		bfsnode now = bfs.pop();

		for (int dir = 0; dir < 4; ++dir) {
			int nx = now.x + dx[dir];
			int ny = now.y + dy[dir];

			if (nx < 1 || nx > n + 1 || ny < 1 || ny > n + 1) continue;
			if (check[nx][ny]) continue;
			if (graph_t[nx][ny] >= sealevel) continue;

			bfs.push(bfsnode(nx, ny));
			check[nx][ny] = true;
		}
	}

	int answer = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (check[i][j]) continue;
			++answer;
		}
	}
	return answer;
}

int maxArea(int M, int mStructure[5], int mSeaLevel)
{
	int answer = -1;
	if (M == 1) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				tempgraph[i][j] = graph[i][j] + mStructure[0];
				answer = max(answer, checkArea(tempgraph, mSeaLevel));
				tempgraph[i][j] = graph[i][j];
			}

		}

		return answer;
	}

	int hash = 0;
	for (int i = 0; i + 1 < M; ++i) {
		hash = hash * 10 + (mStructure[i] - mStructure[i + 1] + 5);
	}

	for (int i = 0; i < hashmap[hash].size; ++i) {
		hashnode wall = hashmap[hash][i];

		if (wall.isHoriz) {
			int height;
			if (wall.isReverse) height = mStructure[0] + graph[wall.x][wall.y + M - 1];
			else height = mStructure[0] + graph[wall.x][wall.y];

			for (int i = 0; i < M; ++i) {
				tempgraph[wall.x][wall.y + i] = height;
			}
			answer = max(answer, checkArea(tempgraph, mSeaLevel));
			for (int i = 0; i < M; ++i) {
				tempgraph[wall.x][wall.y + i] = graph[wall.x][wall.y + i];
			}
		}
		else {
			int height;
			if (wall.isReverse) height = mStructure[0] + graph[wall.x + M - 1][wall.y];
			else height = mStructure[0] + graph[wall.x][wall.y];

			for (int i = 0; i < M; ++i) {
				tempgraph[wall.x + i][wall.y] = height;
			}
			answer = max(answer, checkArea(tempgraph, mSeaLevel));
			for (int i = 0; i < M; ++i) {
				tempgraph[wall.x + i][wall.y] = graph[wall.x + i][wall.y];
			}
		}
	}


	return answer;
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
	freopen("섬지키기.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}
#endif