#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <vector>

int V, E;

//간선 정보를 담는 구조체
//현재 노드와 연결된 노드와 비용을 저장한다.
struct Edge{
	int link;
	int cost;

	//생성자
	Edge(int a, int b) {
		link = a;
		cost = b;
	}

	//기본적으로 priority_queue가 최대 힙으로 사용하므로
	//최소힙을 위해 내가만든 Edge는 반대로 적용
	bool operator<(const Edge& other) const {
		return cost > other.cost;
	}
};
//노드 10000번까지 생성
//각 노드는 연결된 간선정보를 저장
std::vector<Edge> node[10001];

// 힙구조
std::priority_queue<Edge> heap;

// 노드가 연결되었는지 여부를 판단하는 배열
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

	//1번 노드부터 방문하여 시작
	isvisited[1] = true;
	for (int i = 0; i < node[1].size(); i++) {
		heap.push(node[1][i]);
	}

	int count = 1;
	int cost = 0;

	while (!heap.empty()) {
		//최소비용 간선 추출
		Edge top = heap.top();
		heap.pop();

		//이미 연결된 노드이면 패스
		if (isvisited[top.link]) continue;

		// 연결 처리후 비용추가 및 연결된 노드 개수 추가
		isvisited[top.link] = true;
		cost += top.cost;
		count += 1;

		// 모든 노드가 연결되었으면 반복 중지
		if (count == V) break;

		//새로 연결된 노드들 추가
		for (int i = 0; i < node[top.link].size(); i++) {
			heap.push(node[top.link][i]);
		}

	}

	std::cout << cost << '\n';

	return 0;
}