#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>

int T, N, K;
int time[1001];
std::vector<int> rool[1001];
int target;
int answer[1001];
bool check[1001];

int max(int a, int b) {
	if (a > b) return a;
	return b;
}

//필요한 시간을 재귀로 탐색하는 함수
int need_time(int build) {
	//이미 필요한 시간이 계산되었거나, 미리 지어져야하는 빌딩이 있다면 값 반환
	if (rool[build].size() == 0) return time[build];
	if (check[build]) return answer[build];

	// 이전에 지어야 하는 빌딩중 가장 오래걸리는 값 저장
	int temp = 0;
	// 이전에 지어야 하는 빌딩의 필요시간 계산 및 최대값 저장
	for (int i = 0; i < rool[build].size(); i++) {
		temp = max(temp, need_time(rool[build][i]));
	}

	// 필요시간 저장 및 반환
	answer[build] = temp + time[build];
	check[build] = true;

	return answer[build];

}

int solve() {
	// 이전 연산 값 초기화
	for (int i = 0; i < 1001; i++) {
		check[i] = false;
		rool[i].clear();
	}

	// 값 받아오기
	std::cin >> N >> K;
	for (int i = 0; i < N; i++) {
		std::cin >> time[i + 1];
	}
	// 조건은 a빌딩 이전에 지어져하하는 빌딩을 리스트로 저장
	for (int i = 0; i < K; i++) {
		int x, y;
		std::cin >> x >> y;
		rool[y].push_back(x);
	}
	// 최종 빌딩 저장
	std::cin >> target;
	
	//필요시간 계산후 출력
	std::cout << need_time(target) << "\n";

	return 0;
}

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> T;

	// T번의 solve()실행
	for (int t = 0; t < T; t++) {
		solve();
	}

	return 0;

}