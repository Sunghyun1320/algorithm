#define _CRT_SECURE_NO_WARNNINGS

#include <iostream>

int N;
int maxA = 0;
int eleline[500001];
int dp[500001];
int Lsize = 0;
int arr[500001];
int answer[500001];
int remove_count;

int max(int a, int b) {
	if (a > b) return a;
	return b;
}

//LIS�� 2��Ž�� �ڵ�
int lower(int num) {
	
	//dp�� ������ ������ �Է��� ũ�� �߰�
	if (dp[Lsize] < num) {
		dp[++Lsize] = num;
		return Lsize;
	}
	
	//�ƴѰ�� lowerã��
	int left = 1;
	int right = Lsize;
	int mid;

	while (left < right) {
		mid = (left + right) >> 1;

		if (dp[mid] < num) 
			left = mid + 1;
		
		else
			right = mid;

	}

	//lower�� �� �Ҵ� �� ����
	dp[right] = num;
	return right;
}



int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	//�� �Է¹ޱ� �� A�� �ִ밪 �����ϱ�
	std::cin >> N;
	for (int i = 0; i < N; i++) {
		int a, b;
		std::cin >> a >> b;
		maxA = max(maxA, a);
		eleline[a] = b;
	}

	//LIS�� dp�� ���ϰ�, ũ�� ����
	for (int i = 1; i <= maxA; i++) {
		if (eleline[i] == 0) continue;

		arr[i] = lower(eleline[i]);
	}

	// ���־��ϴ� �������� ��ü(N) - LIS(Lsize)
	remove_count = N - Lsize;
	//������ �ӽð�
	int temp = remove_count;
	std::cout << remove_count << "\n";

	// arr�� ����� ���� ���� ���� �迭 ����
	for (int i = maxA; i > 0; i--) {
		if (arr[i] == 0) continue;
		if (Lsize != arr[i]) { answer[temp--] = i; }
		if (Lsize == arr[i]) { Lsize--; }
	}

	//���� ���
	for (int i = 1; i <= remove_count; i++)
		std::cout << answer[i] << "\n";
} 