#if 0
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Node {
	int right;
	int left;
	char alpha;
	int value;

	void clear() {
		right = 0;
		left = 0;
	}
}node[1001];

double cal(int now) {
	if (node[now].alpha == '+')
		return cal(node[now].left) + cal(node[now].right);
	if (node[now].alpha == '-')
		return cal(node[now].left) - cal(node[now].right);
	if (node[now].alpha == '*')
		return cal(node[now].left) * cal(node[now].right);
	if (node[now].alpha == '/')
		return cal(node[now].left) / cal(node[now].right);

	return node[now].value;
}

int solve() {
	int n;
	std::cin >> n;

	for (int i = 1; i <= n; ++i) node[i].clear();

	for (int i = 0; i < n; ++i) {
		int num;
		char alpha;
		std::cin >> num;
		std::cin >> alpha;
		//숫자 입력일 경우
		if (alpha >= 48) {
			node[num].alpha = 0;
			node[num].value = alpha - '0';
			while (1) {
				std::cin.get(alpha);
				if (alpha == ' ' || alpha == '\n') break;
				node[num].value = node[num].value * 10 + alpha - '0';
			}
		}
		//기호 일 경우 반드시 양쪽 자식이 다있어야 한다.
		else {
			node[num].alpha = alpha;
			std::cin >> node[num].left;
			std::cin >> node[num].right;
		}

	}

	return (int)cal(1);
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	freopen("사칙연산_input.txt", "r", stdin);

	for(int tc = 1; tc<= 10; ++tc)
		std::cout << "#" << tc << " " << solve() << "\n";
}
#endif