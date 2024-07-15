#if 1
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

struct List {
	int* data;
	size_t size;
	size_t capasity;

	List(size_t init_size = 2) :size(0), capasity(init_size) {
		data = new int[capasity];
	}
	~List() {
		delete[] data;
	}


	void push(int value) {
		if (capasity == size) {
			resize(capasity * 2);
		}

		data[size++] = value;
	}

	int pop() {
		if (size == 0) {
			std::cerr << "index error list is empty"; return 0;
		}

		return data[size--];

	}




	void resize(size_t new_capasity) {
		int* new_data = new int[new_capasity];
		for (size_t i = 0; i < size; i++) {
			new_data[i] = data[i];
		}
		delete[] data;
		data = new_data;
		capasity = new_capasity;
	}

	int& operator[](size_t index) {
		if (index >= size) {
			std::cerr << "Index error : size over";
			std::exit(EXIT_FAILURE);
		}
		return data[index];
	}


};

List node[14];
int cost[14][14];
int m1, m2, N, x, y, z;

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	freopen("input_19190.txt", "r", stdin);

	int T = 0;
	int testcase = 1;

	std::cin >> T;
	while (T--) {
		std::cin >> N >> m1;

		for (int i = 0; i < m1; ++i) {
			std::cin >> x >> y >> z;
			node[x].push(y);
			node[y].push(x);
			cost[x][y] = z;
			cost[y][x] = z;
		}

		std::cin >> m2;

		for (int i = 0; i < m2; ++i) {
			std::cin >> x >> y >> z;
			node[x].push(y);
			node[y].push(x);
			cost[x][y] = z;
			cost[x][y] = z;
		}
		

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < node[i].size; j++) {
				std::cout << node[i][j] << " ";
			}
			std::cout << "\n";
		}

		std::cout << "##################" << "\n";
	}

}



#endif