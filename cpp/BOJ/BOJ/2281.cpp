#if 0
#include <iostream>

int n, m;

int name[1000];

int note[1000][2];

int count_open(int count) {
	int temp = 0;

	for (int i = 0; i < count; i++) {
		temp += (m - note[i][0]) * (m - note[i][0]);
	}

	return temp;
}


int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> n >> m;
	
	int count = 0;
	int open = 0;
	for (int i = 0; i < n; i++) {
		std::cin >> name[i];
		if (note[count][0] + name[i] >= m) {
			note[count][1] = i - 1;
			open += m - note[count][0];
			count++;
		}

		if (note[count][0]) note[count][0]++;
		note[count][0] += name[i];
	}

	for (int i = 0; i < count; i++) {
		std::cout << note[i][0] << " " << note[i][1] << "\n";
	}

	std::cout << open << "\n";

	




}
#endif