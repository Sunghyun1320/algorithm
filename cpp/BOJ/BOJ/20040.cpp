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

	//�̹� ������ �� ���� true��ȯ
	if (a == b) return true;

	//�ƴѰ�� ���� ���� ���� �� false��ȯ
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
		// Unionó���� �̹� ������ �� ���� ��� ���
		if (Union(a, b)) {
			std::cout << i+1 << "\n";
			check = false;
			break;
		}
	}

	//����� ����Ŭ�� ������ 0���
	if (check) std::cout << 0 << "\n";



	return 0;
}