#include <iostream>

using namespace std;

int temp, cal = 1;
int answer[10] = {0};

int main()
{
	for (int i = 0; i < 3; i++)
	{
		cin >> temp;
		cal *= temp;
	}

	while (1)
	{
		if (cal == 0) break;
		answer[cal % 10] += 1;
		cal = int(cal / 10);
	}

	for (int i = 0; i < 10; i++)
	{
		cout << answer[i] << '\n';
	}


}