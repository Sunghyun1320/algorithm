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
		// 전역 변수 초기화
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

		// 필수 코스 입력받으며 union
		int m1; cin >> m1;
		for (int i = 0; i < m1; i++) {
			int x, y, z; cin >> x >> y >> z;

			//그래프의 차수는 필수 간선만 체크
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

		// 그 외 노드 연결
		int m2; cin >> m2;
		for (int i = 0; i < m2; i++) {
			int x, y, z; cin >> x >> y >> z;
			if (cost[x][y] == 0) cost[x][y] = z;
			if (cost[y][x] == 0) cost[y][x] = z;
			if (cost[x][y] > z) cost[x][y] = z;
			if (cost[y][x] > z) cost[y][x] = z;
		}

		// 필수 노드가 없으면? 그냥 나가자
		if (sum == 0) {
			cout << "#" << tc << " " << sum << "\n";
			continue;
		}

		// 플로이드 워셜로 각 노드간 최단 경로 검색
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

		// 필수 노드로 union된 노드 중, 1번과 연결되지 않은 컴포넌트(루트 노드) 저장
		for (int i = 2; i <= n; i++) {
			if (_find(i) != _find(1) && chk[_find(i)] == 0 && degree[i]) {
				perm[cnt++] = _find(i);
				chk[_find(i)] = 1;
			}
		}

		// dp의 스타트 지점
		// 비트 마스킹으로 표현됨
		// 오일러 경로를 위해 홀수는 1(방문 필요) 짝수는 0(방문 불필요)
		// 오일러 회귀를 위해 모든 노드는 짝수가 되어야 한다.
		// m1경로에 의해 만든 그래프에서
		// 모든 경로를 활용해 홀수 노드를 재 방문하여 짝수로 만든다.
		// 모든 노드가 0이된 dp[0]의 최소값을 찾는 것이다.
		int start = 0;
		for (int i = 1; i <= n; i++) {
			savparents[i] = parents[i];
			start += (degree[i] & 1) * (1 << (i - 1));
		}


		int mini = 1e9;
		do {
			// 유니온된 컴포넌트 저장, dp초기화
			for (int i = 1; i <= n; i++) parents[i] = savparents[i];
			for (int i = 0; i < (1 << n); i++) dp[i] = 0;
			dp[start] = sum;

			// 각 컴포넌트에 대해서
			for (int c = 0; c < cnt; c++) {
				// 루트노드
				int i = perm[c];
				// 1과 다른 컴포넌트여야 하며, 차수가 있어야됌
				// 차수가 없으면 필수로 가야하는 노드가 아니므로 체크 안함
				if (_find(i) != _find(1) && degree[i]) {
					// dp 상태 임시 저장
					for (int cur = 0; cur < (1 << n); cur++) {
						tmp[cur] = dp[cur];
						dp[cur] = 0;
					}

					// 1번 컴포넌트와 연결
					for (int j = 1; j <= n; j++) {
						// j가 1번 컴포넌트와 연결된 노드가 아니면 패스
						if (_find(j) != _find(1)) continue;
						// k는 다른 컴포넌트의 노드
						for (int k = 1; k <= n; k++) {
							// i는 루트노드 
							// 즉 이번에 체크하고자 하는 컴포넌트에 해당하는 노드가 아니면 패스
							if (_find(k) != _find(i)) continue;
							// j에서 k로 가는 경로가 없으면 패스
							if (!cost[j][k]) continue;
							// 모든 경로에 대해서
							for (int cur = 0; cur < (1 << n); cur++) {
								// 이전 dp가  계산되어 있지 않으면 패스
								if (tmp[cur] == 0) continue;
								// xor이므로 원본 데이터 cur에서 j와 k치는 1과 0이 반전되고,
								// 다른 위치는 0이므로 cur의 데이터가 유지된다.
								// 즉 기존 dp에서 j나 k에 해당하는 노드가 짝수 였다면 홀수로
								// 홀수였다면 짝수로 바꾸는 과정이다.
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

			for (int k = 0; k < n; k++) { // 반드시 n번안에는 0으로 바꿀 수 있음이 보장됨
				// 모든 dp에 대해서
				for (int cur = 0; cur < (1 << n); cur++) {
					// i와 j를 선택하여 방문 했을때
					// 최소가 되는 경로를 갱신
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
		// 컴포넌트 연결 순서에따라 경로값이 달라지므로 
		// 모든 순열에 대해서 dp를 구해 줌
		} while (next_permutation(perm, perm + cnt));
		cout << "#" << tc << " " << mini << "\n";
	}
	return 0;
}

#endif
