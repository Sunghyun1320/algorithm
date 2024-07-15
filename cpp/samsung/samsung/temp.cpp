#if 0
#include <iostream>

struct List {
	int* data;       // ���� �迭 ������
	size_t size;     // ���� �迭�� ũ��
	size_t capacity; // �迭�� �뷮

	// ������: �ʱ� �뷮 ����
	List(size_t initial_capacity = 2) : size(0), capacity(initial_capacity) {
		data = new int[capacity];
	}

	// �Ҹ���: ���� �޸� ����
	~List() {
		delete[] data;
	}

	// ���� �߰� (���̽��� append�� ����)
	void push(int value) {
		if (capacity == size) {
			resize(capacity * 2);
		}

		data[size++] = value;
	}

	// �迭 ���Ҵ�
	void resize(size_t new_capacity) {
		int* new_data = new int[new_capacity];
		for (size_t i = 0; i < size; ++i) {
			new_data[i] = data[i];
		}
		delete[] data;
		data = new_data;
		capacity = new_capacity;
	}

	// ���� ũ�� ��ȯ
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
