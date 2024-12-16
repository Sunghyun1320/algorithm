#include <iostream>

using namespace std;

int sum = 0, in, out, answer = 0;

int max(int a, int b)
{
	if (a > b) return a;
	else return b;
}

int main()
{
	for (int i = 0; i < 10; i++)
	{
		cin >> out >> in;

		sum += in;
		sum -= out;

		answer = max(answer, sum);
	}

	cout << answer;

	return 0;


}