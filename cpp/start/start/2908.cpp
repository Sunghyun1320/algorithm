#include <iostream>
#include <string>
using namespace std;


int max(int a,int b)
{
	if (a > b) return a;
	else return b;
}


int main() {

	string a, b, aa, bb;

	cin >> a >> b;

	for(int i = 2; i > -1; i--)
	{
		aa += a[i];
		bb += b[i];
	}

	cout << max(stoi(aa), stoi(bb));

	return 0;
}
