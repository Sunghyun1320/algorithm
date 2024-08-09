#if 0
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

template<typename T>
struct heapq {
	T* data;
	size_t _size;
	size_t capasity;

	heapq(size_t init_size = 2) : _size(0), capasity(init_size) {
		data = new T[capasity];
	}

	~heapq() {
		delete[] data;
	}

	int size() {
		return static_cast<int>(_size);
	}

	void resize(size_t a) {
		T * new_data = new T[a];
		for (size_t i = 0; i < _size; i++) {
			new_data[i] = data[i];
		}
		delete[] data;
		data = new_data;
		capasity = a;
	}

	void push(T value) {
		if (_size == capasity) resize(capasity * 2);
		size_t child = _size;

		while (child > 0) {
			int parindex = (child - 1) >> 1;
			T parent = data[parindex];

			if (value < parent) {
				data[child] = parent;
				child = parindex;
				continue;
			}
			break;
		}

		data[child] = value;
		++_size;
	}

	T pop() {
		if (_size == 0) {
			std::cerr << "index error : heap empty";
			std::exit(EXIT_FAILURE);
		}

		T returnitem = data[0];
		T lastitem = data[--_size];
		data[0] = lastitem;

		int par = 0;

		int child = (par << 1) + 1;
		while (child < size()) {
			int right = child + 1;
			if (right < size() && !(data[child] < data[right])) child = right;

			if (data[child] < lastitem) {
				data[par] = data[child];
				par = child;
				child = (par << 1) + 1;
				continue;
			}
			break;
		}

		data[par] = lastitem;
		return returnitem;
	}

};

int n;
heapq<int> heap;

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> n;
	while (n--) {
		int a;
		std::cin >> a;
		if (a) heap.push(a);
		else {
			if (heap.size()) std::cout << heap.pop() << "\n";
			else std::cout << 0 << "\n";
		}
	}

}

#endif
