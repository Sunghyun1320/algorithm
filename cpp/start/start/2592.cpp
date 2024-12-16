#include <iostream>

using namespace std;

int temp, sum = 0;
int count_[1000] = {0};



int main()
{
	for (int i = 0; i < 10; i++)
	{
		cin >> temp;
		sum += temp;
		count_[temp] += 1;
	}

	cout << int(sum / 10) << '\n';

	int max_index = -1, max_count = -1;

	for (int i = 0; i < 1000; i++)
	{
		if (max_count < count_[i])
		{
			max_count = count_[i];
			max_index = i;

		}
	}

	cout << max_index << endl;



}