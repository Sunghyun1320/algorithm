#if 0
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

template<typename T>
struct Stack {
	T* data;
	size_t _size;
	size_t capasity;

	Stack(size_t init_size = 2) : _size(0), capasity(init_size){
		data = new T[capasity];
	}

	~Stack() {
		delete[] data;
	}

	int size() { return static_cast<int>(_size); }

	void clear() {
		_size = 0;
	}

	void push(T value) {
		if (capasity == _size) {
			resize(capasity * 2);
		}

		data[_size++] = value;
	}

	void resize(size_t new_capasity) {
		T* new_data = new T[new_capasity];
		for (size_t i = 0; i < _size; i++) 
			new_data[i] = data[i];
		delete[] data;
		data = new_data;
		capasity = new_capasity;
	}

	T pop() {
		if (_size == 0) {
			std::cerr << "index error : list is empty";
			std::exit(EXIT_FAILURE);
		}

		return data[--_size];
	}

	T& operator[](size_t index) {
		if (index >= _size) {
			std::cerr << "index error : size over";
			std::exit(EXIT_FAILURE);
		}

		return data[index];
	}
	
};


int min(int a, int b) {
	if (a < b) return a;
	return b;
}

int max(int a, int b) {
	if (a < b) return b;
	return a;
}


Stack<int> stack;
Stack<int> node[10001];
Stack<int> cost[10001];
int n, m;
int factory1, factory2;
bool visited[10001];

bool dfs(int start, int end, int min_cost) {
	for (int i = 0; i < n; i++) visited[i] = false;
	stack.push(start);
	visited[start] = true;

	while (stack.size()) {
		int now = stack.pop();

		if (now == end) return true;

		for (int i = 0; i < node[now].size(); i++) {
			if (visited[node[now][i]] || cost[now][i] < min_cost)
				continue;

			visited[node[now][i]] = true;
			stack.push(node[now][i]);
		}


	}

	return false;
}


int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> n >> m;
	
	for (int i = 0; i < m; i++) {
		int a, b, c;
		std::cin >> a >> b >> c;

		node[a].push(b);
		node[b].push(a);
		cost[a].push(c);
		cost[b].push(c);
		
	}

	std::cin >> factory1 >> factory2;


	int left = 1;
	int right = int(1e9);
	int answer = 0;

	while (left <= right) {
		int mid = (left + right) >> 1;
		if (dfs(factory1, factory2, mid)) {
			answer = mid;
			left = mid + 1;
		}
		else right = mid - 1;

	}

	std::cout << answer << "\n";
}

#endif