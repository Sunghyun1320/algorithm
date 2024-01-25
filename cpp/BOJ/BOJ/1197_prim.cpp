#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <vector>

int V, E;

//���� ������ ��� ����ü
//���� ���� ����� ���� ����� �����Ѵ�.
struct Edge{
	int link;
	int cost;

	//������
	Edge(int a, int b) {
		link = a;
		cost = b;
	}

	//�⺻������ priority_queue�� �ִ� ������ ����ϹǷ�
	//�ּ����� ���� �������� Edge�� �ݴ�� ����
	bool operator<(const Edge& other) const {
		return cost > other.cost;
	}
};
//��� 10000������ ����
//�� ���� ����� ���������� ����
std::vector<Edge> node[10001];

// ������
std::priority_queue<Edge> heap;

// ��尡 ����Ǿ����� ���θ� �Ǵ��ϴ� �迭
bool isvisited[10001] = { false };

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> V >> E;

	for (int i = 0; i < E; i++) {
		int a, b, c;
		std::cin >> a >> b >> c;

		node[a].push_back(Edge(b,c));
		node[b].push_back(Edge(a,c));
	}

	//1�� ������ �湮�Ͽ� ����
	isvisited[1] = true;
	for (int i = 0; i < node[1].size(); i++) {
		heap.push(node[1][i]);
	}

	int count = 1;
	int cost = 0;

	while (!heap.empty()) {
		//�ּҺ�� ���� ����
		Edge top = heap.top();
		heap.pop();

		//�̹� ����� ����̸� �н�
		if (isvisited[top.link]) continue;

		// ���� ó���� ����߰� �� ����� ��� ���� �߰�
		isvisited[top.link] = true;
		cost += top.cost;
		count += 1;

		// ��� ��尡 ����Ǿ����� �ݺ� ����
		if (count == V) break;

		//���� ����� ���� �߰�
		for (int i = 0; i < node[top.link].size(); i++) {
			heap.push(node[top.link][i]);
		}

	}

	std::cout << cost << '\n';

	return 0;
}