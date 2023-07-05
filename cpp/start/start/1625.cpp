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
	//최대 깊이에서 리턴
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

	//최소횟수가 아니면 리턴
	if (count >= min_count) return;

	//이미 맞는 위치면 다음 열
	if (compare(my_row[depth], depth))
	{
		dfs(depth + 1);
		return;
	}


	int map_depth = depth + 1;

	while (map_depth < m)
	{
		//해당 열이 이미 맞으면 다음 열 체크
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

	//값 초기화
	min_count = 1 << 20;
	count = 0;
	for (int i = 0; i < 256; i++)
		my_row[i] = i;

	//데이터 입력 받기
	std::cin >> n >> m;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			std::cin >> map[i][j];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			std::cin >> answer[i][j];


	//바꿔야 하는 행 체크
	for (int i = 0; i < n; i++)
	{
		int map_count_zero = 0;
		int answer_count_zero = 0;
		for (int j = 0; j < m; j++)
		{
			if (map[i][j] == 0) map_count_zero++;
			if (answer[i][j] == 0) answer_count_zero++;
		}

		// 해당 행의 0의 개수가 같다면 이상 무
		if (map_count_zero == answer_count_zero)
		{

		}

		// 0이 다른데 합이 m이라면 뒤집혀야 하는 행
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
		// 그 외의 경우엔 최종 전구색을 만들 수 없다.
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

