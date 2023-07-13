#include <iostream>
#include <queue>

int N, M;

struct edge
{
	int node_a, node_b;
	int cost;

	edge(int a, int b, int c) : node_a(a), node_b(b), cost(c) {};

	bool operator<(const edge e) const {
		return this->cost < e.cost;
	}
};

std::priority_queue<edge> heap;
int parents[100001];
int count_child[100000];
unsigned int sum, answer;

void union_f(int a, int b)
{
	a = parents[a];
	b = parents[b];

	if (a == b) return;

	answer = (answer + sum * count_child[a] * count_child[b]) % 1000000000;

	if (a > b)
	{
		parents[a] = b;
		count_child[b] += count_child[a];
	}

	else if (a < b)
	{
		parents[b] = a;
		count_child[a] += count_child[b];
	}

	return;

}

int find(int a)
{
	if (parents[a] != a)
		parents[a] = find(parents[a]);

	return parents[a];
}


int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	for (int i = 0; i < 100000; i++)
	{
		parents[i] = i;
		count_child[i] = 1;
	}


	std::cin >> N >> M;

	for (int i = 0; i < M; i++)
	{
		int a, b, c;
		std::cin >> a >> b >> c;
		sum += c;

		heap.push(edge(a, b, c));
	}


	while (!heap.empty())
	{
		edge temp = heap.top();
		heap.pop();

		int a = temp.node_a, b = temp.node_b, c = temp.cost;

		union_f(a, b);
		sum -= c;
	}

	std::cout << answer;

	return 0;
}