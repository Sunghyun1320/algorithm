#if 0
#define _CRT_SECURE_NO_WARNINGS

#define INF 98765432
#include <iostream>

int cost[501][501];

int min(int a, int b) { return a > b ? b : a; }
int max(int a, int b) { return a > b ? a : b; }


void solve(int tc) {
	int N, M;
	std::cin >> N >> M;

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) 
			cost[i][j] = INF;
		cost[i][i] = 0;
	}

	while (M--) {
		int a, b, c;
		std::cin >> a >> b >> c;
		cost[a][b] = min(cost[a][b], c);
	}
	
	for(int k = 1; k<=N; ++k)
		for (int i = 1; i <= N; ++i) 
			for (int j = 1; j <= N; ++j) {
				if (cost[i][k] == INF || cost[k][j] == INF) continue;
				cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
			}

	std::cout << "#" << tc << " ";
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (cost[i][j] == INF) cost[i][j] = -1;
			std::cout << cost[i][j] << " ";
		}
	}
	std::cout << "\n";
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	int T; std::cin >> T;

	for (int tc = 1; tc <= T; ++tc)
		solve(tc);

}
#endif