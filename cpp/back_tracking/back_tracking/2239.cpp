#include <iostream>

using namespace std;

int sudoku[9][9];

bool check(int x, int y, int num)
{
	for (int i = 0; i < 9; i++)
	{
		if (sudoku[i][y] == num) return false;
		if (sudoku[x][i] == num) return false;
	}

	int nx = int(x / 3) * 3;
	int ny = int(y / 3) * 3;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (sudoku[nx + i][ny + j] == num) return false;
		}
	}

	return true;

}



void solve(int depth)
{
	if (depth == 81)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
				cout << sudoku[i][j];
			cout << "\n";
		}
		exit(0);
	}

	int x = int(depth / 9);
	int y = depth % 9;

	if (sudoku[x][y] != 0)
	{
		solve(depth + 1);
		return;
	}

	for (int i = 1; i < 10; i++)
	{
		if (check(x, y, i))
		{
			sudoku[x][y] = i;
			solve(depth + 1);
			sudoku[x][y] = 0;
		}
	}


}

int main()
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			scanf("%1d", &sudoku[i][j]);


	solve(0);
	

}

