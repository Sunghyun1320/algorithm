#if 0
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Node {
	int x;
	int y;

	bool operator<(const Node& other) {
		if (x == other.x) return y < other.y;
		return x < other.x;
	}
}node[100000];

void merge_sort(int left, int right, Node* arr) {
	if (left >= right) return;

	int mid = (left + right) >> 1;

	merge_sort(left, mid, arr);
	merge_sort(mid + 1, right, arr);

	int i = left;
	int j = mid + 1;
	Node * temp = new Node[right - left + 1];
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


int solve() {
	int N;
	std::cin >> N;

	for (int i = 0; i < N; ++i) {
		int a, b;
		std::cin >> a >> b;
		node[i] = { a,b };
	}

	merge_sort(0, N - 1, node);


}


int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	int T;
	std::cin >> T;
	for (int tc = 1; tc <= T; ++tc)
		std::cout << "#" << tc << " " << solve() << "\n";
}


#endif