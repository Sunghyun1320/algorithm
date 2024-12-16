#if 0
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>

int open_stack[1001], close_stack[1001];

void solve(int tc) {
	int n;
	std::cin >> n;

	open_stack[0] = 0;
	close_stack[0] = 0;

	for (int i = 0; i < n; ++i) {
		char temp;
		std::cin >> temp;

		if (temp == '(') open_stack[++open_stack[0]] = i;
		else if(open_stack[0]) --open_stack[0];
		else close_stack[++close_stack[0]] = i;
	}

	if (n & 1) {
		std::cout << "#" << tc << " -1\n";
		return;
	}

	if (!open_stack[0] && !close_stack[0]) {
		std::cout << "#" << tc << " 0\n";
		return;
	}

	if (!open_stack[0]) {
		std::cout << "#" << tc << " 1\n";
		std::cout << close_stack[1] << " " << close_stack[close_stack[0] >> 1] << "\n";
		return;
	}

	if (!close_stack[0]) {
		std::cout << "#" << tc << " 1\n";
		std::cout << open_stack[(open_stack[0] >> 1) + 1] << " " << open_stack[open_stack[0]] << "\n";
		return;
	}
	
	if (close_stack[0] > open_stack[0]) {
		std::cout << "#" << tc << " 2\n";
		std::cout << open_stack[1] << " " << open_stack[open_stack[0]] << "\n";
		std::cout << close_stack[1] << " " << close_stack[(close_stack[0] + open_stack[0]) >> 1] << "\n";
		return;
	}

	if (close_stack[0] < open_stack[0]) {
		std::cout << "#" << tc << " 2\n";
		std::cout << close_stack[1] << " " << close_stack[close_stack[0]] << "\n";
		int mid = open_stack[0] - ((close_stack[0] + open_stack[0]) >> 1) + 1;
		std::cout << open_stack[mid] << " " << open_stack[open_stack[0]] << "\n";
		return;
	}

	std::cout << "#" << tc << " 2\n";
	std::cout << open_stack[1] << " " << open_stack[open_stack[0]] << "\n";
	std::cout << close_stack[1] << " " << close_stack[close_stack[0]] << "\n";


}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	freopen("°ýÈ£_input.txt", "r", stdin);

	int T;
	std::cin >> T;

	for (int tc = 1; tc <= T; ++tc)
		solve(tc);
}


#endif