#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

long long a, b;

// a������ 1�� ���� ���� ���ϴ� �Լ�
// x = a * 2^n + b * 2^n-1 + c
// f(x) = a * 2^n-1 + b*c
long long countsumone(long long a) {
	//�ڸ���
	int i = 1;
	//��ȯ��
	long long sum = 0;
	//������
	long long rest = 0;
	while (a) {
		rest |= (a & 1LL) << (i-1);
		// �� ��ŭ ����
		sum += (a >> 1) * (1LL << (i - 1));
		// ������ ó��
		sum += (rest >> (i-1)) * (rest - (1LL << (i - 1)));
		a = a >> 1;
		i++;

	}

	return sum;
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> a >> b;

	std::cout << countsumone(b+1) - countsumone(a) << "\n";


	return 0;
}