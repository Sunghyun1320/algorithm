#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int N, r[500], c[500], dp[501][501];

int main(){
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> N;
	for (int i = 0; i < N; i++) 
		std::cin >> r[i] >> c[i];

	// �̿��� 2���� ����ȸ�� ����
	for (int i = 0; i < N - 1; i++)
		dp[i][i + 1] = r[i] * c[i] * c[i + 1];

	// 3���� ������ üũ
	for (int inter = 2; inter < N; inter++) {
		// 0~2, 1~3, 2~4�� ������� �ּҿ��� ���ϱ�
		for (int left = 0; left < N - inter; left++) {
			int right = left + inter;
			// left ~ right���� �߰��� i�� ����
			for (int i = left; i < right; i++) {
				// �߰��� i�϶��� ���� Ƚ��
				int temp = dp[left][i] + dp[i + 1][right] + r[left] * c[i] * c[right];
				// ������� ���ų� �ּҰ��̸� ����
				if (dp[left][right] == 0 || dp[left][right] > temp) dp[left][right] = temp;
			}
		}

	}

	// 0~N-1���� Ƚ�� ���
	std::cout << dp[0][N - 1];

	return 0;
}

