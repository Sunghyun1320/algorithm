#if 0
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>

struct Edge {
	int a;
	int b;
	int cost;

	bool operator<(const Edge& other) {
		return cost < other.cost;
	}
}edge[200000];

void merge_sort(int left, int right, Edge * arr) {
	if (left >= right) return;

	int mid = (left + right) >> 1;

	merge_sort(left, mid, arr);
	merge_sort(mid + 1, right, arr);

	int i = left;
	int j = mid + 1;
	Edge* temp = new Edge[right - left + 1];
	int k = 0;

	while (i <= mid && j <= right) {
		if (arr[i] < arr[j]) temp[k++] = arr[i++];
		else temp[k++] = arr[j++];
	}

	while (i <= mid) temp[k++] = arr[i++];
	while (j <= right) temp[k++] = arr[j++];

	for (int i = 0; i < right - left + 1; ++i) arr[left + i] = temp[i];

	delete[] temp;
}



int root[50001];
int Find(int a) {
	if (root[a] != a) root[a] = Find(root[a]);
	return root[a];
}

bool Union(int a, int b) {
	a = Find(a);
	b = Find(b);

	if (a == b) return false;

	if (a < b) root[b] = a;
	else root[a] = b;

	return true;
}

int solve() {
	int N, M;
	std::cin >> N >> M;

	for (int i = 1; i <= N; ++i)
		root[i] = i;

	for (int i = 0; i < M; ++i) 
		std::cin >> edge[i].a >> edge[i].b >> edge[i].cost;

	merge_sort(0, M - 1, edge);

	int answer = 0;
	for (int i = 0; i < M; ++i)
		if (Union(edge[i].a, edge[i].b)) answer += edge[i].cost;

	return answer;
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	freopen("고속도로건설2.txt", "r", stdin);

	int T;
	std::cin >> T;

	for (int tc = 1; tc <= T; ++tc)
		std::cout << "#" << tc << " " << solve() << "\n";
}

#endif