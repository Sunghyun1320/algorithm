#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int N, M, m[100], c[100], dp[101][10001];

int max(int a, int b) {
	if (a > b) return a;
	return b;
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	// �� �Է¹ޱ�
	std::cin >> N >> M;

	for (int i = 0; i < N; i++) {
		std::cin >> m[i];
	}
	
	for (int i = 0; i < N; i++) {
		std::cin >> c[i];
	}

	// N���� �ۿ� ���ؼ�
	for (int i = 0; i < N; i++) {
		// �ִ� 10000�� �ҿ�ð��� �ɸ���
		//�� �ҿ�ð��� ���ؼ� ���� �� �ִ� �ִ� �޸� ���
		for (int j = 0; j < 10001; j++) {
			// ���� ���� �ҿ�ð��� Ž���ϴ� �ҿ�ð����� ũ�� ��Ȱ��ȭ �Ұ�
			// ���� dp�� ���� �޾ƿ�
			if (c[i] > j) dp[i+1][j] = dp[i][j];
			// ���� ���� �ҿ�ð��� Ž���ϴ� �ҿ�ð����� ������ dpüũ
			// ��Ȱ��ȭ�� ��� dp[i][j-c[i]] + m[i], Ȱ��ȭ �ϰ�� dp[i][j]
			// �� ���� ū �� ����
			else {
				dp[i+1][j] = max(dp[i][j], dp[i][j - c[i]]+m[i]);
 			}
		}
	}


	// �ҿ�ð����� �޸𸮰� M�̻��̸� ��� �� ����
	for (int i = 0; i < 10001; i++) {
		if (dp[N][i] >= M) {
			std::cout << i;
			break;

		}
	}

	return 0;
}