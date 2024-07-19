#if 1
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

// �Է¹޴� ����
int N, m1, m2;

// �ּҰ� dp�� �ӽ������ dp
int sum;
int start;
int dp[1 << 13];
int temp_dp[1 << 13];
int min_answer;

// �� ��尣 �ִ� �Ÿ�
int cost[14][14];

// union�� ������ ��Ʈ���
int root[14];
int saveroot[14];

// union�� �� ������Ʈ
int component[14];
// union�� ������Ʈ ����
int count;
// component�����ÿ� perm������ ����ϴ� check
int check[14];

// ���Ϸ� ��θ� ���� ����
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
	// root ����
	for (int i = 1; i <= N; ++i) root[i] = saveroot[i];
	//dp�ʱ�ȭ
	for (int i = 0; i < (1 << N); ++i) dp[i] = 0;
	dp[start] = sum;

	//�� ������Ʈ�� ���ؼ�
	for (int com = 0; com < count; com++) {
		// ������ ���� ������ ������Ʈ ����
		int i = perm[com];
		// 1���� �ٸ� ������Ʈ ����
		if (Find(i) == Find(1) || degree[i] == 0) continue;

		// dp�ӽ�����
		for (int state = 0; state < (1 << N); ++state) {
			temp_dp[state] = dp[state];
			dp[state] = 0;
		}

		// 1�� ���ϴ� j����
		for (int j = 1; j <= N; ++j) {
			if (Find(j) != Find(1)) continue;

			// i�� ���ϴ� k����
			for (int k = 1; k <= N; ++k) {
				if (Find(k) != Find(i)) continue;
				// jk��� ������ ����
				if (cost[j][k] == 0) continue;

				// ��� ���¿� ���ؼ� j�� k�� ����� ���¸� ����
				for (int state = 0; state < (1 << N); ++state) {
					// ��ΰ� ������ �н�
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

//���� ���� ����Լ�
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

	//�������� �ʱ�ȭ
	for (int i = 1; i <= N; ++i) 
		for (int j = 1; j <= N; ++j) 
			cost[i][j] = 0;
		
	for (int i = 0; i <= N; ++i) {
		root[i] = i;
		check[i] = 0;
		degree[i] = 0;
	}
	
	// �ʼ� ��� �Է¹ޱ�
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

	// �÷��̵� ����
	for (int k = 1; k <= N; ++k) {
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				if (cost[i][k] == 0 || cost[k][j] == 0) continue;
				if(cost[i][j] == 0 || cost[i][j] > cost[i][k] + cost[k][j])
					cost[i][j] = cost[i][k] + cost[k][j];
			}
		}
	}

	// 1�� ������� ���� ������Ʈ�� ���� ����
	count = 0;
	for (int i = 2; i <= N; ++i) {
		if (Find(i) != Find(1) && check[Find(i)] == 0 && degree[i] != 0) {
			component[count++] = Find(i);
			check[Find(i)] = 1;
		}
	}

	start = 0;
	// union�� ���¸� ���� �����ϰ�, start�� ���
	for (int i = 1; i <= N; ++i) {
		saveroot[i] = root[i];
		start += (degree[i] & 1) * (1 << (i - 1));
	}

	// ������ ���� üũ �ʱ�ȭ
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