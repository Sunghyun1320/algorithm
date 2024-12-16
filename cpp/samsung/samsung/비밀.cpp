#if 0
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int max(int a, int b) { return a > b ? a : b; }

int n, k;
bool child[11][11];
int count[11];
bool iscycle[11];
int answer;

void dfs(int now, int depth) {
	if (iscycle[now]) return;

	answer = max(answer, depth);

	iscycle[now] = true;
	
	int max_value = 0;
	for (int i = 1; i <= n; ++i) 
		if(child[now][i]) dfs(i, depth+1);
	iscycle[now] = false;

}

void solve(int tc) {
	for (int i = 0; i <= 10; ++i) {
		for (int j = 0; j <= 10; ++j) {
			child[i][j] = false;
		}
		count[i] = 0;
		iscycle[i] = false;
	}

	std::cin >> n >> k;

	while (k--) {
		int m;
		std::cin >> m;

		int a, b;
		std::cin >> a;
		--m;
		while (m--) {
			std::cin >> b;
			child[a][b] = true;
			a = b;
		}
	}

	for (int i = 1; i <= 10; ++i) 
		for (int j = 1; j <= 10; ++j) {
			if (child[i][j]) ++count[i];
		}

	answer = 0;
	for (int i = 1; i <= n; ++i) dfs(i, 0);

	std::cout << "#" << tc << " ";
	for (int i = 1; i <= n; ++i) {
		std::cout << count[i] << " ";
	}
	std::cout << answer+1 << "\n";

}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	freopen("ºñ¹Ð_input.txt", "r", stdin);

	int T;
	std::cin >> T;
	for (int tc = 1; tc <= T; ++tc)
		solve(tc);
}
#endif