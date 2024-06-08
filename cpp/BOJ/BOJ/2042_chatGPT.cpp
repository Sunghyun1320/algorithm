#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>

int N, M, K;
long long a, b;
std::vector<long long> seg_tree;

// ���� �޾� ���׸�Ʈ Ʈ���� �����Ѵ�.
void init() {
	int size = 1;
	while (size < N) {
		size <<= 1;
	}

	seg_tree.resize(size * 2);

	// �Է� ���� ���� ��忡 ����
	for (int i = 0; i < N; i++) {
		std::cin >> seg_tree[size + i];
	}

	// ���� ��带 �������� �θ� ��忡 �ڽ� ����� ���� ����
	for (int i = size - 1; i > 0; i--) {
		seg_tree[i] = seg_tree[i * 2] + seg_tree[i * 2 + 1];
	}
}

// Ư�� ���� �ٲٴ� �Լ�
void change() {
	std::cin >> a >> b;
	// �ε����� -1
	int pos = a - 1;
	int size = seg_tree.size() / 2;

	// ���� ��� �� ����
	pos += size;
	seg_tree[pos] = b;

	// �θ� ��带 Ž���ϸ� ���� ����
	while (pos > 1) {
		pos /= 2;
		seg_tree[pos] = seg_tree[pos * 2] + seg_tree[pos * 2 + 1];
	}
}

// ���� ���� ã�� �Լ�
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
