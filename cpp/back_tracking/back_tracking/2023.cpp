#include<iostream>

using namespace std;

int start_num[4] = { 2, 3, 5, 7 };
int prime_num[4] = { 1, 3, 7, 9 };

int n;

bool check_prime(int num)
{
	for (int i = 2; i < int(num / 2); i++)
	{
		if (num % i == 0) return false;
	}
	return true;
}


void solve(int depth, int max_depth, int num)
{
	if (depth == max_depth)
	{
		if (check_prime(num))
		{
			cout << num << endl;
			return;
		}
	}

	if (!check_prime(num)) return;



	for (int i = 0; i < 4; i++) 
	{
		solve(depth + 1, max_depth, num * 10 + prime_num[i]);
	}

}

int main()
{
	cin >> n;

	for (int i = 0; i < 4; i++)
	{
		solve(1, n, start_num[i]);
	}
}



