#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int N, M;

int graph[500000];

int Find(int a) {
	if (graph[a] != a)
		graph[a] = Find(graph[a]);

	return graph[a];
}

bool Union(int a, int b) {
	a = Find(a);
	b = Find(b);

	//이미 합쳐진 두 노드면 true반환
	if (a == b) return true;

	//아닌경우 작은 값에 붙인 후 false반환
	if (a > b) {
		graph[b] = a;
		return false;
	}
	graph[a] = b;
	return false;

}


int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	
	std::cin >> N >> M;

	for (int i = 0; i < N; i++) graph[i] = i;
	
	int a, b;
	bool check = true;
	for (int i = 0; i < M; i++) {
		std::cin >> a >> b;
		// Union처리후 이미 합쳐진 두 노드면 결과 출력
		if (Union(a, b)) {
			std::cout << i+1 << "\n";
			check = false;
			break;
		}
	}

	//결과가 사이클이 없으면 0출력
	if (check) std::cout << 0 << "\n";



	return 0;
}