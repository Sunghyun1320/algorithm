#define _crt_secure_no_warnning

#include<iostream>
int n, m, k, size, a;
long long b;

long long arr[2100000];

//���� �޾� ���׸�Ʈ Ʈ���� �����Ѵ�.
void init() {
	size = 1;
	//n�� �´� �ִ� ���� Ž��
	while (size < n) 
		size = size << 1;
	

	// �ִ� ���̿� �迭 ����
	for (int i = 0; i < n; i++) {
		std::cin >> arr[size + i];
	}

	// ���� �θ��忡 �ڽĳ���� ���� ����
	for (int i = size - 1; i >= 0; i--) {
			arr[i] = arr[i * 2] + arr[i * 2 + 1];
	}
}


// Ư�� ���� �ٲٴ� �Լ�
void change() {
	std::cin >> a >> b;
	// �ε����� -1
	a = a - 1 + size;

	// ���� �ٲ� ��
	arr[a] = b;

	// �θ��带 Ž���ϸ� ���� ����
	while(a>1){
		a = a >> 1;
		arr[a] = arr[a * 2] + arr[a * 2 + 1];
	}
}

long long answer() {
	std::cin >> a >> b;
	// size���� ����ؼ� �ڽ��� �� ã��
	a = a - 1 + size;
	b = b - 1 + size;

	// ���� ��
	long long sum = 0;

	// a�� ��� Ȧ���̸� ���� ���ϰ� ¦���̸� �θ𿡼� ���Ѵ�.
	// b�� ��� ¦���̸� ���� ���ϰ� Ȧ���̸� �θ𿡼� ���Ѵ�.
	while (a <= b) {
		if (a % 2 == 1) sum += arr[a++];
		if (b % 2 == 0) sum += arr[b--];
		a /= 2;
		b /= 2;
	}

	return sum;


}


int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> n >> m >> k;

	init();

	int order;

	for (int i = 0; i < m + k; i++) {
		std::cin >> order;
		if (order % 2) change();
		else std::cout << answer() << "\n";
	}
}


