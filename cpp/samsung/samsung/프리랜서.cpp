#if 0
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Schedule {
	int start;
	int end;
	int pay;

	bool operator<(const Schedule& other) {
		return start < other.start;
	}
}schedule[501];


template<typename T>
void merge_sort(int left, int right, T* arr) {
	if (left >= right) return;

	int mid = (left + right) >> 1;
	merge_sort(left, mid, arr);
	merge_sort(mid + 1, right, arr);

	int i = left;
	int j = mid + 1;

	int k = 0;
	T* temp = new T[right - left + 1];

	while (i <= mid && j <= right) {
		if (arr[i] < arr[j]) temp[k++] = arr[i++];
		else temp[k++] = arr[j++];
	}

	while (i <= mid) temp[k++] = arr[i++];
	while (j <= right) temp[k++] = arr[j++];

	for (int i = 0; i < right - left + 1; ++i) arr[left + i] = temp[i];

	delete[] temp;
}

int max(int a, int b) { return a > b ? a : b; }

int dp[501][10000];

int solve() {
	int n, m;
	std::cin >> n >> m;

	for (int i = 1; i <= n; ++i) 
		std::cin >> schedule[i].start >> schedule[i].end >> schedule[i].pay;
	
	merge_sort(1, n, schedule);

	for (int i = 1; i <= n; ++i) {
		dp[i][schedule[i].end] = max(dp[i - 1][schedule[i].end], dp[i - 1][schedule[i].start - 1] + schedule[i].pay);
		for (int j = 1; j < schedule[i].end; ++j) dp[i][j] = dp[i - 1][j];
		for (int j = schedule[i].end; j <= m; ++j)
			dp[i][j] = max(dp[i][schedule[i].end], dp[i-1][j]);
	}

	return dp[n][m];
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0), std::cout.tie(0);
	freopen("프리랜서_input.txt","r",stdin);

	int T; std::cin >> T;
	for (int tc = 1; tc <= T; ++tc) 
		std::cout << "#" << tc << " " << solve() << "\n";
	
}


#endif