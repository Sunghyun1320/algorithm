#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

int N, M, cow_x, horse_x;

int horse_z[500000], cow_z[500000], sort_temp[500000];

int min(int a, int b)
{
	return a < b ? a : b;
}

int abs(int a)
{
	return a > 0 ? a : -a;
}

void sort(int n, int* arr, int left, int right)
{
	if (right - left == 1)
	{
		if (arr[left] > arr[right])
		{
			int temp = arr[left];
			arr[left] = arr[right];
			arr[right] = temp;
		}
		return;
	}

	if (right == left) return;

	int mid = (left + right) / 2;
	sort(n, arr, left, mid);
	sort(n, arr, mid + 1, right);


	int a = left, b = mid + 1;
	int i = left;

	while (a <= mid || b <= right)
	{
		if (a == mid + 1)
			sort_temp[i++] = arr[b++];
		else if (b == right + 1)
			sort_temp[i++] = arr[a++];


		else if (arr[a] < arr[b])
			sort_temp[i++] = arr[a++];

		else
			sort_temp[i++] = arr[b++];
	}

	for (int i = left; i <= right; i++)
		arr[i] = sort_temp[i];
	

	return;
}


void solve(int test_case)
{
	int answer = 1000000000, count = 0;
	std::cin >> N >> M >> cow_x >> horse_x;

	for (int i = 0; i < N; i++)
		std::cin >> cow_z[i];

	for (int i = 0; i < M; i++)
		std::cin >> horse_z[i];

	sort(N, cow_z, 0, N - 1);
	sort(M, horse_z, 0, M - 1);


	int j = 0;
	for (int i = 0; i < N; i++)
	{
		if (j == M) break;
		
		int before = abs(cow_z[i] - horse_z[j]);
		int now;

		while (j <= M)
		{
			if (j == M)
			{
				if (answer == before) count++;
				else if (answer > before)
				{
					answer = before;
					count = 1;
				}
				break;
			}


			now = abs(cow_z[i] - horse_z[j]);
			if(now > before)
			{
				if (answer == before) count++;
				else if (answer > before)
				{
					answer = before;
					count = 1;
				}
				break;
			}

			else if (now == before)
			{
				if (answer == before) count += 2;
				else if (answer > before)
				{
					answer = before;
					count = 2;
				}
				
				break;
			}

			else
			{
				before = now;
				j++;
			}

		}

	}

	std::cout << "#" << test_case << " " << answer + abs(horse_x - cow_x) << " " << count << "\n";


}



int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	freopen("input_0701_28.txt", "r", stdin);

	int T;
	std::cin >> T;

	for (int test_case = 1; test_case <= T; test_case++)
		solve(test_case);

	//int a_arr[10] = { 1,3,7,29,11,13,31,15,31,22 };
	//sort(10, a_arr, 0, 9);

	//for (int i = 0; i < 10; i++)
	//	std::cout << a_arr[i] << " ";

	return 0;
}