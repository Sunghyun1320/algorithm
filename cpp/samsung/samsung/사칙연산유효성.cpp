#if 0
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>

struct Stack {
	int data[201];
	int size;

	void clear() { size = 0; }
	void push(int value) { data[size++] = value; }
	int pop() { return data[--size]; }
	int operator[](int index) { return data[index]; }
};

struct Node {
	int left;
	int right;
	char alpha;

	void clear() {
		left = 0;
		right = 0;
	}
}node[201];
Stack dfs;

int solve() {
	int n;
	std::cin >> n;
	for (int i = 1; i <= n; ++i) node[i].clear();

	for (int i = 0; i < n; ++i) {
		int num;
		char alpha;
		std::cin >> num;
		std::cin >> alpha;

		node[num].alpha = alpha;

		bool isleft = true;
		while (1) {
			std::cin.get(alpha);
			if (alpha == '\n') break;

			if (alpha == ' ' && isleft) {
				std::cin >> node[num].left;
				isleft = false;
				continue;
			}

			std::cin >> node[num].right;
			break;
		}
	}

	dfs.clear();
	dfs.push(1);

	while (dfs.size) {
		int now_num = dfs.pop();
		Node now = node[now_num];

		// 연산인 경우 자식이 2개 다 있어야 됨
		if (now.alpha == '+' || now.alpha == '-' || now.alpha == '*' || now.alpha == '/') {
			if (!now.left || !now.right) return 0;
			dfs.push(now.left);
			dfs.push(now.right);
			continue;
		}

		// 숫자인경우 자식이 있으면 안됨
		if (now.left || now.right) return 0;
	}

	return 1;
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	freopen("사칙연산유효성_input.txt", "r", stdin);

	for (int tc = 1; tc <= 10; ++tc)
		std::cout << "#" << tc << " " << solve() << "\n";
}
#endif 