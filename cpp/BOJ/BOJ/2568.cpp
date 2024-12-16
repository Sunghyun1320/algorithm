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

//LIS용 2진탐색 코드
int lower(int num) {
	
	//dp의 마지막 값보다 입력이 크면 추가
	if (dp[Lsize] < num) {
		dp[++Lsize] = num;
		return Lsize;
	}
	
	//아닌경우 lower찾기
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

	//lower에 값 할당 후 리턴
	dp[right] = num;
	return right;
}



int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	//값 입력받기 및 A의 최대값 저장하기
	std::cin >> N;
	for (int i = 0; i < N; i++) {
		int a, b;
		std::cin >> a >> b;
		maxA = max(maxA, a);
		eleline[a] = b;
	}

	//LIS용 dp를 구하고, 크기 저장
	for (int i = 1; i <= maxA; i++) {
		if (eleline[i] == 0) continue;

		arr[i] = lower(eleline[i]);
	}

	// 없애야하는 전깃줄은 전체(N) - LIS(Lsize)
	remove_count = N - Lsize;
	//복구용 임시값
	int temp = remove_count;
	std::cout << remove_count << "\n";

	// arr에 저장된 값에 따라 정답 배열 생성
	for (int i = maxA; i > 0; i--) {
		if (arr[i] == 0) continue;
		if (Lsize != arr[i]) { answer[temp--] = i; }
		if (Lsize == arr[i]) { Lsize--; }
	}

	//정답 출력
	for (int i = 1; i <= remove_count; i++)
		std::cout << answer[i] << "\n";
} 