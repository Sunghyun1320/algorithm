#include <iostream>

using namespace std;

int temp, sum, answer, max_sum = 0;

int main()
{
	for (int i = 0; i < 5; i++)
	{
		sum = 0;
		for (int j = 0; j < 4; j++)
		{
			cin >> temp;
			sum += temp;
		}

		if (sum > max_sum)
		{
			answer = i + 1;
			max_sum = sum;
		}
	}


	cout << answer << " " << max_sum << endl;
	


}