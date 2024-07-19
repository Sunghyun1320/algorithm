#if 0
#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <iostream>

using namespace std;

int cost[14][14];

int parents[14];
int savparents[14];

int degree[14];

int dp[1 << 13];
int tmp[1 << 13];

int chk[14];

int cnt = 0;
int perm[14];

int _find(int u) {
	return u == parents[u] ? u : parents[u] = _find(parents[u]);
}

void _union(int u, int v) {
	u = _find(u);
	v = _find(v);
	if (u == v) return;
	parents[v] = u;
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	freopen("input_19190.txt", "r", stdin);

	int t; cin >> t;
	for (int tc = 1; tc <= t; tc++) {
		int n; cin >> n;
		// ���� ���� �ʱ�ȭ
		int sum = 0;
		cnt = 0;

		for (int i = 1; i <= n; i++) {
			parents[i] = i;
			degree[i] = 0;
			chk[i] = 0;
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cost[i][j] = 0;
			}
		}

		// �ʼ� �ڽ� �Է¹����� union
		int m1; cin >> m1;
		for (int i = 0; i < m1; i++) {
			int x, y, z; cin >> x >> y >> z;

			//�׷����� ������ �ʼ� ������ üũ
			degree[x]++;
			degree[y]++;
			if (x > y) swap(x, y);
			_union(x, y);
			sum += z;
			if (cost[x][y] == 0) cost[x][y] = z;
			if (cost[y][x] == 0) cost[y][x] = z;
			if (cost[x][y] > z) cost[x][y] = z;
			if (cost[y][x] > z) cost[y][x] = z;
		}

		// �� �� ��� ����
		int m2; cin >> m2;
		for (int i = 0; i < m2; i++) {
			int x, y, z; cin >> x >> y >> z;
			if (cost[x][y] == 0) cost[x][y] = z;
			if (cost[y][x] == 0) cost[y][x] = z;
			if (cost[x][y] > z) cost[x][y] = z;
			if (cost[y][x] > z) cost[y][x] = z;
		}

		// �ʼ� ��尡 ������? �׳� ������
		if (sum == 0) {
			cout << "#" << tc << " " << sum << "\n";
			continue;
		}

		// �÷��̵� ���ȷ� �� ��尣 �ִ� ��� �˻�
		for (int k = 1; k <= n; k++) {
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++) {
					if (!cost[i][k] || !cost[k][j]) continue;
					if (cost[i][j] == 0 || cost[i][j] > cost[i][k] + cost[k][j]) {
						cost[i][j] = cost[i][k] + cost[k][j];
					}
				}
			}
		}

		// �ʼ� ���� union�� ��� ��, 1���� ������� ���� ������Ʈ(��Ʈ ���) ����
		for (int i = 2; i <= n; i++) {
			if (_find(i) != _find(1) && chk[_find(i)] == 0 && degree[i]) {
				perm[cnt++] = _find(i);
				chk[_find(i)] = 1;
			}
		}

		// dp�� ��ŸƮ ����
		// ��Ʈ ����ŷ���� ǥ����
		// ���Ϸ� ��θ� ���� Ȧ���� 1(�湮 �ʿ�) ¦���� 0(�湮 ���ʿ�)
		// ���Ϸ� ȸ�͸� ���� ��� ���� ¦���� �Ǿ�� �Ѵ�.
		// m1��ο� ���� ���� �׷�������
		// ��� ��θ� Ȱ���� Ȧ�� ��带 �� �湮�Ͽ� ¦���� �����.
		// ��� ��尡 0�̵� dp[0]�� �ּҰ��� ã�� ���̴�.
		int start = 0;
		for (int i = 1; i <= n; i++) {
			savparents[i] = parents[i];
			start += (degree[i] & 1) * (1 << (i - 1));
		}


		int mini = 1e9;
		do {
			// ���Ͽµ� ������Ʈ ����, dp�ʱ�ȭ
			for (int i = 1; i <= n; i++) parents[i] = savparents[i];
			for (int i = 0; i < (1 << n); i++) dp[i] = 0;
			dp[start] = sum;

			// �� ������Ʈ�� ���ؼ�
			for (int c = 0; c < cnt; c++) {
				// ��Ʈ���
				int i = perm[c];
				// 1�� �ٸ� ������Ʈ���� �ϸ�, ������ �־�߉�
				// ������ ������ �ʼ��� �����ϴ� ��尡 �ƴϹǷ� üũ ����
				if (_find(i) != _find(1) && degree[i]) {
					// dp ���� �ӽ� ����
					for (int cur = 0; cur < (1 << n); cur++) {
						tmp[cur] = dp[cur];
						dp[cur] = 0;
					}

					// 1�� ������Ʈ�� ����
					for (int j = 1; j <= n; j++) {
						// j�� 1�� ������Ʈ�� ����� ��尡 �ƴϸ� �н�
						if (_find(j) != _find(1)) continue;
						// k�� �ٸ� ������Ʈ�� ���
						for (int k = 1; k <= n; k++) {
							// i�� ��Ʈ��� 
							// �� �̹��� üũ�ϰ��� �ϴ� ������Ʈ�� �ش��ϴ� ��尡 �ƴϸ� �н�
							if (_find(k) != _find(i)) continue;
							// j���� k�� ���� ��ΰ� ������ �н�
							if (!cost[j][k]) continue;
							// ��� ��ο� ���ؼ�
							for (int cur = 0; cur < (1 << n); cur++) {
								// ���� dp��  ���Ǿ� ���� ������ �н�
								if (tmp[cur] == 0) continue;
								// xor�̹Ƿ� ���� ������ cur���� j�� kġ�� 1�� 0�� �����ǰ�,
								// �ٸ� ��ġ�� 0�̹Ƿ� cur�� �����Ͱ� �����ȴ�.
								// �� ���� dp���� j�� k�� �ش��ϴ� ��尡 ¦�� ���ٸ� Ȧ����
								// Ȧ�����ٸ� ¦���� �ٲٴ� �����̴�.
								int nxt = cur ^ ((1 << (j - 1)) + (1 << (k - 1)));
								if (dp[nxt] == 0 || dp[nxt] > tmp[cur] + cost[j][k]) {
									dp[nxt] = tmp[cur] + cost[j][k];
								}
							}
						}
					}
					_union(1, i);
				}
			}

			for (int k = 0; k < n; k++) { // �ݵ�� n���ȿ��� 0���� �ٲ� �� ������ �����
				// ��� dp�� ���ؼ�
				for (int cur = 0; cur < (1 << n); cur++) {
					// i�� j�� �����Ͽ� �湮 ������
					// �ּҰ� �Ǵ� ��θ� ����
					for (int i = 1; i <= n; i++) {
						for (int j = i + 1; j <= n; j++) {
							if (!cost[i][j]) continue;
							if (dp[cur] == 0) continue;
							int hap = ((1 << (i - 1)) + (1 << (j - 1)));
							if (i == j) hap = 0;;
							int nxt = cur ^ hap;
							if (dp[nxt] == 0 || dp[nxt] > dp[cur] + cost[i][j]) {
								dp[nxt] = dp[cur] + cost[i][j];
							}
						}
					}
				}
			}

			if (dp[0] != 0) mini = min(mini, dp[0]);
		// ������Ʈ ���� ���������� ��ΰ��� �޶����Ƿ� 
		// ��� ������ ���ؼ� dp�� ���� ��
		} while (next_permutation(perm, perm + cnt));
		cout << "#" << tc << " " << mini << "\n";
	}
	return 0;
}

#endif
