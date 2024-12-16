#if 0
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Node {
	int left;
	int right;
	char alpha;

	void clear() {
		left = 0;
		right = 0;
	}
}node[101];

void in_order(int now) {
	if (node[now].left) in_order(node[now].left);
	std::cout << node[now].alpha;
	if (node[now].right) in_order(node[now].right);
}

void solve(int tc) {
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

	std::cout << "#" << tc << " ";
	in_order(1);
	std::cout << "\n";


}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	freopen("중위순회_input.txt", "r", stdin);

	for (int tc = 1; tc <= 10; ++tc)
		solve(tc);
}



#endif