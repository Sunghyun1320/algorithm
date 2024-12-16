#include<iostream>

using namespace std;

int answer[42], temp, count_;

int main()
{
	for (int i = 0; i < 10; i++)
	{
		cin >> temp;
		answer[temp % 42] += 1;
	}

	for (int i = 0; i < 42; i++)
		if (answer[i] != 0) count_ += 1;

	cout << count_ << endl;


}