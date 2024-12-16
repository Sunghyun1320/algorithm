#include <iostream>
#include <string>

using namespace std;

int T, point;
string str;


int main()
{
	cin >> T;

	for (int i = 0; i < T; i++)
	{
		cin >> point >> str;

		for (int j = 0; j < str.length(); j++)
		{
			if (point-1 == j) continue;
			cout << str[j];
		}
		cout << endl;
		
	}


	
}