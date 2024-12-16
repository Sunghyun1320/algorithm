#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int N, r[500], c[500], dp[501][501];

int main(){
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> N;
	for (int i = 0; i < N; i++) 
		std::cin >> r[i] >> c[i];

	// 이웃한 2개의 연산회수 저장
	for (int i = 0; i < N - 1; i++)
		dp[i][i + 1] = r[i] * c[i] * c[i + 1];

	// 3개의 묶음씩 체크
	for (int inter = 2; inter < N; inter++) {
		// 0~2, 1~3, 2~4의 방식으로 최소연산 구하기
		for (int left = 0; left < N - inter; left++) {
			int right = left + inter;
			// left ~ right까지 중간점 i를 구함
			for (int i = left; i < right; i++) {
				// 중간점 i일때의 연산 횟수
				int temp = dp[left][i] + dp[i + 1][right] + r[left] * c[i] * c[right];
				// 연산된적 없거나 최소값이면 갱신
				if (dp[left][right] == 0 || dp[left][right] > temp) dp[left][right] = temp;
			}
		}

	}

	// 0~N-1까지 횟수 출력
	std::cout << dp[0][N - 1];

	return 0;
}

