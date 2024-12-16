#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>

int N, M, K;
long long a, b;
std::vector<long long> seg_tree;

// 값을 받아 세그먼트 트리로 저장한다.
void init() {
	int size = 1;
	while (size < N) {
		size <<= 1;
	}

	seg_tree.resize(size * 2);

	// 입력 값을 리프 노드에 저장
	for (int i = 0; i < N; i++) {
		std::cin >> seg_tree[size + i];
	}

	// 리프 노드를 기준으로 부모 노드에 자식 노드의 합을 저장
	for (int i = size - 1; i > 0; i--) {
		seg_tree[i] = seg_tree[i * 2] + seg_tree[i * 2 + 1];
	}
}

// 특정 값을 바꾸는 함수
void change() {
	std::cin >> a >> b;
	// 인덱스는 -1
	int pos = a - 1;
	int size = seg_tree.size() / 2;

	// 리프 노드 값 변경
	pos += size;
	seg_tree[pos] = b;

	// 부모 노드를 탐색하며 합을 갱신
	while (pos > 1) {
		pos /= 2;
		seg_tree[pos] = seg_tree[pos * 2] + seg_tree[pos * 2 + 1];
	}
}

// 구간 합을 찾는 함수
long long find(int left, int right) {
	long long sum = 0;
	int size = seg_tree.size() / 2;
	left += size;
	right += size;

	while (left <= right) {
		if (left % 2 == 1) sum += seg_tree[left++];
		if (right % 2 == 0) sum += seg_tree[right--];
		left /= 2;
		right /= 2;
	}

	return sum;
}

void print() {
	std::cin >> a >> b;
	std::cout << find(a - 1, b - 1) << "\n";
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> N >> M >> K;

	init();

	int order;

	for (int i = 0; i < M + K; i++) {
		std::cin >> order;
		if (order == 1) change();
		else print();
	}

	return 0;
}
