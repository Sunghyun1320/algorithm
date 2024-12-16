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

bool check(int min_x, int min_y, int max_x, int max_y, Node a) {
	if ((a.y - node[min_x].y) * (node[max_y].x - node[min_x].x) > (a.x - node[min_x].x) * (node[max_y].y - node[min_x].y))
		return true;

	if ((a.y - node[min_x].y) * (node[min_y].x - node[min_x].x) < (a.x - node[min_x].x) * (node[min_y].y - node[min_x].y))
		return true;

	if ((a.y - node[max_x].y) * (node[max_x].x - node[max_y].x) > (a.x - node[max_x].x) * (node[max_x].y - node[max_y].y))
		return true;

	if ((a.y - node[max_x].y) * (node[max_x].x - node[min_y].x) < (a.x - node[max_x].x) * (node[max_x].y - node[min_y].y))
		return true;

	return false;
}

int solve() {
	int N;
	std::cin >> N;

	for (int i = 0; i < N; ++i) {
		int a, b;
		std::cin >> a >> b;
		node[i] = { a,b };
	}

	merge_sort(0, N-1, node);

	int min_y = 0, max_y = 0;
	for (int i = 0; i < N; ++i) {
		if (node[min_y].y >= node[i].y) min_y = i;
		if (node[max_y].y < node[i].y) max_y = i;
	}

	int answer = 4;
	for (int i = 1; i < N - 1; ++i) {
		if (check(0, min_y, N - 1, max_y, node[i])) 
			++answer;
	}

	return answer;

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