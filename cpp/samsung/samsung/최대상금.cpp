#if 0
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>

int max(int a, int b) {
	if (a < b) return b;
	return a;
}

struct List {
	int data[10];
	int sorted[10];
	int size;

	bool issame() {
		for (int i = 0; i < size; ++i) {
			if (data[i] != sorted[i]) return false;
		}
		return true;
	}

	int value() {
		int returnvalue = 0;
		for (int i = 0; i < size; ++i) {
			returnvalue = returnvalue * 10 + data[i];
		}

		return returnvalue;
	}

	void push(int value) {
		size = 0;
		while (value) {
			data[size++] = value % 10;
			value /= 10;
		}
		int temp;
		for (int i = 0; i < size >> 1; ++i) {
			temp = data[i];
			data[i] = data[size - i - 1];
			data[size - i - 1] = temp;
		}
	}

	// 선택정렬 이후 여유있으면 nlogn으로 변경
	void sort() {
		for (int i = 0; i < size; ++i) sorted[i] = data[i];

		for (int i = 0; i < size - 1; ++i) {
			int max_value = -1;
			int index = i;
			for (int j = i; j < size; ++j) {
				if (max_value < sorted[j]) {
					max_value = sorted[j];
					index = j;
				}
			}
			sorted[index] = sorted[i];
			sorted[i] = max_value;
		}
	}

	int operator[](int index) {
		return data[index];
	}
};

List data;
int input, count, answer;

void solve(int depth = 0) {
	if (depth == count) {
		answer = max(answer, data.value());
		return;
	}

	if (data.issame()) {
		if ((count - depth) & 1) {
			int check[10] = { 0 };
			for (int i = 0; i < data.size; ++i) {
				++check[data[i]];
				if (check[data[i]] >= 2) {
					answer = max(answer, data.value());
					return;
				}
			}

			int temp = data[data.size - 1];
			data.data[data.size - 1] = data[data.size - 2];
			data.data[data.size - 2] = temp;

			answer = max(answer, data.value());

			data.data[data.size - 2] = data[data.size - 1];
			data.data[data.size - 1] = temp;
		}
		else
			answer = max(answer, data.value());

		return;
	}

	for (int i = 0; i < data.size; ++i) {
		if (data[i] == data.sorted[i]) continue;

		for (int j = i+1; j < data.size; ++j) {
			if (data[j] == data.sorted[i]) {
				int temp = data[i];
				data.data[i] = data[j];
				data.data[j] = temp;

				solve(depth + 1);
				data.data[j] = data[i];
				data.data[i] = temp;
			}
		}

	}
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	freopen("최대상금_input.txt", "r", stdin);

	int T;

	std::cin >> T;

	for (int tc = 1; tc <= T; ++tc) {
		std::cin >> input >> count;

		data.push(input);
		data.sort();
		answer = 0;

		solve();

		std::cout << "#" << tc << " " << answer << "\n";
	}
}


#endif