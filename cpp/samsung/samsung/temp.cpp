#if 0
#include <iostream>

struct List {
	int* data;       // 동적 배열 포인터
	size_t size;     // 현재 배열의 크기
	size_t capacity; // 배열의 용량

	// 생성자: 초기 용량 설정
	List(size_t initial_capacity = 2) : size(0), capacity(initial_capacity) {
		data = new int[capacity];
	}

	// 소멸자: 동적 메모리 해제
	~List() {
		delete[] data;
	}

	// 원소 추가 (파이썬의 append와 유사)
	void push(int value) {
		if (capacity == size) {
			resize(capacity * 2);
		}

		data[size++] = value;
	}

	// 배열 재할당
	void resize(size_t new_capacity) {
		int* new_data = new int[new_capacity];
		for (size_t i = 0; i < size; ++i) {
			new_data[i] = data[i];
		}
		delete[] data;
		data = new_data;
		capacity = new_capacity;
	}

	// 현재 크기 반환
	size_t getSize() const {
		return size;
	}
};

int main() {
	List myList;
	myList.push(10);
	myList.push(20);
	myList.push(30);

	std::cout << "Current size of the list: " << myList.getSize() << std::endl;

	return 0;
}
#endif
