#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

int LOG = 0;

int V, E, node_1, node_2;

std::vector< std::vector<int> > tree(10001);
std::vector<int> level(10001, -1);
std::vector<int> childnode(10001, -1);
std::vector< std::vector<int> > graph(10001);
//************************************************************************
int dfs(int node)
{
	int my_sub = 0;

	for (int i = 0; i < int(graph[node].size()) ; i++)
	{
		level[graph[node][i]] = level[node] + 1;
		tree[graph[node][i]][0] = node;
		my_sub += dfs(graph[node][i]);
	}

	childnode[node] = my_sub + 1;

	return my_sub + 1;

}


//************************************************************************
void solve(int test_case)
{
	//값 초기화
	LOG = 0;

	std::cin >> V >> E >> node_1 >> node_2;

	//2진 탐색을 위한 LOG값 구하기
	while (true)
	{
		if ((1 << LOG) > V)
		{
			LOG += 1;
			break;
		}
		LOG += 1;
	}

	for (int i = 0; i < 10001; i++)
	{
		std::vector<int> temp(LOG, 0), temp2;
		tree[i] = temp;
		level[i] = -1;
		childnode[i] = -1;
		graph[i] = temp2;
	}

	//************************************************************************
	// 트리를 그래프 형태로 저장

	for (int i = 0; i < E; i++)
	{
		int a, b;
		std::cin >> a >> b;
		graph[a].push_back(b);
	}

	level[1] = 0;
	childnode[1] = dfs(1);
	//************************************************************************

	//2진 형태로 조상 노드를 구해 줌
	for (int i = 1; i < LOG; i++)
		for (int j = 1; j <= V ; j++)
			tree[j][i] = tree[tree[j][i - 1]][i - 1];


	//node_1의 레벨이 높도록 조절 해줌
	if (level[node_1] < level[node_2])
	{
		int temp = node_1;
		node_1 = node_2;
		node_2 = temp;
	}

	//레벨을 서로 맞춰 줌
	for (int i = LOG - 1; i > -1; i--)
	{
		if (level[node_1] - level[node_2] >= (1 << i))
			node_1 = tree[node_1][i];
	}

	//만약 같으면 출력 후 리턴
	if (node_1 == node_2)
	{
		std::cout << "#"<< test_case << " " << node_1 << " " << childnode[node_1] <<"\n";
		return;
	}

	//아니면 부모노드 찾아가기
	for (int i = LOG - 1; i > -1; i--)
	{
		if (tree[node_1][i] != tree[node_2][i])
		{
			node_1 = tree[node_1][i];
			node_2 = tree[node_2][i];
		}
	}

	std::cout << "#" << test_case << " " << tree[node_1][0] << " " << childnode[tree[node_1][0]] << "\n";


}


int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	freopen("input_0610_3.txt", "r", stdin);

	int T;
	std::cin >> T;

	for (int test_case = 1; test_case <= T; test_case++)
	{
		solve(test_case);
	}


	return 0;
}
