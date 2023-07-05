#include <iostream>
#include <vector>

int n, m, count, min_count;

int my_row[256];

bool map[256][256];
bool answer[256][256];

std::vector<char> row;
std::vector<std::pair<char, char>> col;

std::vector<std::pair<char, char>> col_answer;



bool compare(int a, int b)
{
	for (int i = 0; i < n; i++)
	{
		if (map[i][a] != answer[i][b])
			return false;
	}

	return true;
}

void dfs(int depth)
{
	//�ִ� ���̿��� ����
	if (depth >= m)
	{
		if (count < min_count)
		{
			min_count = count;
			col_answer.clear();
			for (std::pair<int, int> a : col)
				col_answer.push_back(a);
		}
		return;
	}

	//�ּ�Ƚ���� �ƴϸ� ����
	if (count >= min_count) return;

	//�̹� �´� ��ġ�� ���� ��
	if (compare(my_row[depth], depth))
	{
		dfs(depth + 1);
		return;
	}


	int map_depth = depth + 1;

	while (map_depth < m)
	{
		//�ش� ���� �̹� ������ ���� �� üũ
		if (compare(my_row[map_depth], map_depth))
		{
			map_depth++;
			continue;
		}

		if (compare(my_row[map_depth], depth))
		{
			int temp = my_row[map_depth];
			my_row[map_depth] = my_row[depth];
			my_row[depth] = temp;
			col.push_back({ depth + 1, map_depth + 1 });
			count++;
			dfs(depth + 1);
			count--;
			my_row[depth] = my_row[map_depth];
			my_row[map_depth] = temp;
			col.pop_back();
		}

		map_depth++;
	}

}

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	//�� �ʱ�ȭ
	min_count = 1 << 20;
	count = 0;
	for (int i = 0; i < 256; i++)
		my_row[i] = i;

	//������ �Է� �ޱ�
	std::cin >> n >> m;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			std::cin >> map[i][j];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			std::cin >> answer[i][j];


	//�ٲ�� �ϴ� �� üũ
	for (int i = 0; i < n; i++)
	{
		int map_count_zero = 0;
		int answer_count_zero = 0;
		for (int j = 0; j < m; j++)
		{
			if (map[i][j] == 0) map_count_zero++;
			if (answer[i][j] == 0) answer_count_zero++;
		}

		// �ش� ���� 0�� ������ ���ٸ� �̻� ��
		if (map_count_zero == answer_count_zero)
		{

		}

		// 0�� �ٸ��� ���� m�̶�� �������� �ϴ� ��
		else if (map_count_zero + answer_count_zero == m)
		{
			for (int j = 0; j < m; j++)
			{
				map[i][j] = ~map[i][j];
				answer[i][j] = ~answer[i][j];
			}
			count++;
			row.push_back(i + 1);
			//std::cout << "0 " << i + 1 << "\n";
		}
		// �� ���� ��쿣 ���� �������� ���� �� ����.
		else
		{
			std::cout << "-1\n";
			return 0;
		}
	}

	dfs(0);


	if (min_count == 1 << 20)
	{
		std::cout << "-1\n";
		return 0;
	}

	std::cout << min_count << "\n";
	for (int a : row)
		std::cout << "0 " << a << "\n";
	for (std::pair<int, int> a : col_answer)
		std::cout << "1 " << a.first << " " << a.second << "\n";

	
	return 0;
}

