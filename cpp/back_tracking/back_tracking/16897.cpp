#include <iostream>

using namespace std;

int n, egg[8][2], answer;

int max(int a,int b)
{
	if (a > b) return a;
	else return b;
}



void back(int depth, int max_depth, int count) 
{
	if (answer == n) return;
	if (depth == max_depth || count == max_depth - 1)
	{
		answer = max(answer, count);
		return;
	}

	if (egg[depth][0] == 0)
	{
		back(depth + 1, max_depth, count); 
		return;
	}

	for (int i = 0; i < n; i++)
	{
		if (i == depth || egg[i][0] == 0) continue;
		
		int temp[2] = { egg[i][0], egg[depth][0] };
		int count_temp = count;

		egg[i][0] -= egg[depth][1];
		egg[depth][0] -= egg[i][1];
		
		if (egg[i][0] <= 0)
		{
			egg[i][0] = 0;
			count_temp += 1;
		}
		if (egg[depth][0] <= 0)
		{
			egg[depth][0] = 0;
			count_temp += 1;
		}

		back(depth + 1, max_depth, count_temp);

		egg[i][0] = temp[0];
		egg[depth][0] = temp[1];

	}
}

int main()
{
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		cin >> egg[i][0] >> egg[i][1];
	}


	back(0, n, 0);

	cout << answer << endl;



}