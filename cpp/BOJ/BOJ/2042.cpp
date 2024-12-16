#define _crt_secure_no_warnning

#include<iostream>
int n, m, k, size, a;
long long b;

long long arr[2100000];

//값을 받아 세그먼트 트리로 저장한다.
void init() {
	size = 1;
	//n에 맞는 최대 깊이 탐색
	while (size < n) 
		size = size << 1;
	

	// 최대 깊이에 배열 저장
	for (int i = 0; i < n; i++) {
		std::cin >> arr[size + i];
	}

	// 이후 부모노드에 자식노드의 합을 저장
	for (int i = size - 1; i >= 0; i--) {
			arr[i] = arr[i * 2] + arr[i * 2 + 1];
	}
}


// 특정 값을 바꾸는 함수
void change() {
	std::cin >> a >> b;
	// 인덱스는 -1
	a = a - 1 + size;

	// 값을 바꾼 후
	arr[a] = b;

	// 부모노드를 탐색하며 합을 갱신
	while(a>1){
		a = a >> 1;
		arr[a] = arr[a * 2] + arr[a * 2 + 1];
	}
}

long long answer() {
	std::cin >> a >> b;
	// size까지 고려해서 자신의 값 찾기
	a = a - 1 + size;
	b = b - 1 + size;

	// 정답 값
	long long sum = 0;

	// a의 경우 홀수이면 지금 더하고 짝수이면 부모에서 더한다.
	// b의 경우 짝수이면 지금 더하고 홀수이면 부모에서 더한다.
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


