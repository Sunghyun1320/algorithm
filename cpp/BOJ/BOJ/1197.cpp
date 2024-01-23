#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>

int V, E, answer;

//�� ����� ��Ʈ�� ����
int root[10001];

// union-find����� ���� �Լ�
int Find(int a) {
	if (root[a] != a) root[a] = Find(root[a]);
	return root[a];
}

bool Union(int a, int b) {
	a = Find(a);
	b = Find(b);

	if (a == b) return false;

	if (a < b) root[b] = a;
	else root[a] = b;

	return true;
}

// ���� ����ü
struct Edge {
	int a;
	int b;
	int cost;

	//������ ���� ���۷����� ����
	bool operator<(const Edge& other) const {
		return cost < other.cost;
	}
} edge[100000];



int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> V >> E;

	//�ʱ� ����� ��Ʈ���� �ڽ�
	for (int i = 1; i <= V; i++) root[i] = i;

	// E���� �Է¹ޱ�
	for (int i = 0; i < E; i++) {
		std::cin >> edge[i].a >> edge[i].b >> edge[i].cost;
	}

	// E������ ����
	std::sort(std::begin(edge), std::begin(edge)+E);

	//MST
	answer = 0;
	for (int i = 0; i < E; i++) {
		if (Union(edge[i].a, edge[i].b)) answer += edge[i].cost;
	}

	std::cout << answer << "\n";


	return 0;
}