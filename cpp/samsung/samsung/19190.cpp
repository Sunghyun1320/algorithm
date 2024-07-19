#if 1
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

// 입력받는 변수
int N, m1, m2;

// 최소값 dp와 임시저장용 dp
int sum;
int start;
int dp[1 << 13];
int temp_dp[1 << 13];
int min_answer;

// 각 노드간 최단 거리
int cost[14][14];

// union된 노드들의 루트노드
int root[14];
int saveroot[14];

// union된 각 컴포넌트
int component[14];
// union된 컴포넌트 개수
int count;
// component생성시와 perm생성시 사용하는 check
int check[14];

// 오일러 경로를 위한 차수
int degree[14];

int perm[14];

int Find(int a) {
	if (a != root[a]) root[a] = Find(root[a]);
	return root[a];
}

void Union(int a, int b) {
	a = Find(a);
	b = Find(b);

	if (a < b) root[b] = a;
	else root[a] = b;

	return;
}

void dp_cal() {
	// root 복구
	for (int i = 1; i <= N; ++i) root[i] = saveroot[i];
	//dp초기화
	for (int i = 0; i < (1 << N); ++i) dp[i] = 0;
	dp[start] = sum;

	//각 컴포넌트에 대해서
	for (int com = 0; com < count; com++) {
		// 순열에 의해 생성된 컴포넌트 선택
		int i = perm[com];
		// 1번과 다른 컴포넌트 선택
		if (Find(i) == Find(1) || degree[i] == 0) continue;

		// dp임시저장
		for (int state = 0; state < (1 << N); ++state) {
			temp_dp[state] = dp[state];
			dp[state] = 0;
		}

		// 1에 속하는 j선택
		for (int j = 1; j <= N; ++j) {
			if (Find(j) != Find(1)) continue;

			// i에 속하는 k선택
			for (int k = 1; k <= N; ++k) {
				if (Find(k) != Find(i)) continue;
				// jk경로 없으면 다음
				if (cost[j][k] == 0) continue;

				// 모든 상태에 대해서 j와 k가 연결된 상태를 구함
				for (int state = 0; state < (1 << N); ++state) {
					// 경로가 없으면 패스
					if (temp_dp[state] == 0) continue;

					int next = state ^ ((1 << (j - 1)) + (1 << (k - 1)));
					if (dp[next] == 0 || dp[next] > temp_dp[state] + cost[j][k]) 
						dp[next] = temp_dp[state] + cost[j][k];
				}
			}

		}
		Union(1, i);
	}

	for (int _ = 0; _ < N; ++_) {
		for (int state = 0; state < (1 << N); ++state) {
			for (int i = 1; i <= N; ++i) {
				for (int j = i + 1; j <= N; ++j) {
					if (cost[i][j] == 0) continue;
					if (dp[state] == 0) continue;

					int next = state ^ ((1 << (i - 1)) + (1 << (j - 1)));
					if (dp[next] == 0 || dp[next] > dp[state] + cost[i][j])
						dp[next] = dp[state] + cost[i][j];
				}
			}
		}
	}

	if (dp[0] != 0 && min_answer > dp[0])  min_answer = dp[0];

}

//순열 생성 재귀함수
void permutation(int depth = 0) {
	if (depth == count) {
		dp_cal();
		return;
	}

	for (int i = 0; i < count; ++i) {
		if (check[i]) continue;
		check[i] = 1;
		perm[depth] = component[i];
		permutation(depth + 1);
		check[i] = 0;
	}
}

int solve() {
	std::cin >> N;

	//전역변수 초기화
	for (int i = 1; i <= N; ++i) 
		for (int j = 1; j <= N; ++j) 
			cost[i][j] = 0;
		
	for (int i = 0; i <= N; ++i) {
		root[i] = i;
		check[i] = 0;
		degree[i] = 0;
	}
	
	// 필수 노드 입력받기
	sum = 0;
	std::cin >> m1;
	for (int i = 0; i < m1; ++i) {
		int x, y, z;
		std::cin >> x >> y >> z;
		++degree[x];
		++degree[y];
		Union(x, y);

		sum += z;
		if (!cost[x][y]) cost[x][y] = z;
		if (!cost[y][x]) cost[y][x] = z;
		if (cost[x][y] > z) cost[x][y] = z;
		if (cost[y][x] > z) cost[y][x] = z;
	}

	std::cin >> m2;
	for (int i = 0; i < m2; ++i) {
		int x, y, z;
		std::cin >> x >> y >> z;

		if (!cost[x][y]) cost[x][y] = z;
		if (!cost[y][x]) cost[y][x] = z;
		if (cost[x][y] > z) cost[x][y] = z;
		if (cost[y][x] > z) cost[y][x] = z;
	}

	if (sum == 0) return 0;

	// 플루이드 워셜
	for (int k = 1; k <= N; ++k) {
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				if (cost[i][k] == 0 || cost[k][j] == 0) continue;
				if(cost[i][j] == 0 || cost[i][j] > cost[i][k] + cost[k][j])
					cost[i][j] = cost[i][k] + cost[k][j];
			}
		}
	}

	// 1과 연결되지 않은 컴포넌트는 따로 저장
	count = 0;
	for (int i = 2; i <= N; ++i) {
		if (Find(i) != Find(1) && check[Find(i)] == 0 && degree[i] != 0) {
			component[count++] = Find(i);
			check[Find(i)] = 1;
		}
	}

	start = 0;
	// union된 상태를 따로 저장하고, start를 계산
	for (int i = 1; i <= N; ++i) {
		saveroot[i] = root[i];
		start += (degree[i] & 1) * (1 << (i - 1));
	}

	// 재사용을 위한 체크 초기화
	for (int i = 0; i <= N; ++i) check[i] = 0;
	min_answer = int(1e9);
	permutation();

	return min_answer;

}



int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	freopen("input_19190.txt", "r", stdin);

	int T = 0;
	int testcase = 1;

	std::cin >> T;
	while (T--) {
		std::cout << "#" << testcase++ << " " << solve() << "\n";
	}

}

#endif