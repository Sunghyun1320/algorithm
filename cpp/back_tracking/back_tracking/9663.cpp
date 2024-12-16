#include <iostream>

using namespace std;

//int n;
//int answer[] = { 0,1,0,0,2,10,4,40,92,352,724,2680,14200,73712,365596,2279184 };
//
//
//int main()
//{
//	cin >> n;
//	cout << answer[n];
//}

/*======================================================================*/

int n;
int answer = 0;
int arr[15];

int local_arr[15];


void find(int max_depth, int depth = 0)
{
	if (depth == max_depth) 
	{
		answer += 1;
		return;
	}

	copy(begin(arr), end(arr), begin(local_arr));

	for (int i = 0; i < max_depth; i++)
	{
		if (arr[i] == -1) continue;

		int x = depth - arr[i];
		int a = i + x, b = i - x;

		if (a >= 0 && a < max_depth && arr[a] == -1) local_arr[a] = arr[i];
		if (b >= 0 && b < max_depth && arr[b] == -1) local_arr[b] = arr[i];

	}

	for (int i = 0; i < max_depth; i++)
	{
		if (local_arr[i] == -1) 
		{
			arr[i] = depth;
			find(max_depth, depth+1);
			arr[i] = 0;
				
		}

	}

}





int main()
{
	cin >> n;
	for (int i = 0; i < 15; i++) arr[i] = -1;

	find(n);

	cout << answer;



}