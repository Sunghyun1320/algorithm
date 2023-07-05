#include<iostream>

using namespace std;

int main()
{
	int a, b;
	cin >> a >> b;

	int sum = 0, sum_a, sum_b;
	int count = 0;

	bool check = false;

	for (int i = 1; i <= b; i++)
	{
		for (int j = 0; j < i; j++)
		{
			sum += i;
			count += 1;
			if (count == a) sum_a = sum - i;
			if (count == b)
			{
				sum_b = sum;
				check = true;
				break;
			}
		}

		if (check) break;

	}

	cout << sum_b - sum_a << endl;

	return 0;
}