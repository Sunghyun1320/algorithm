#include <iostream>

int test_case;
int main()
{
	std::cin >> test_case;

	for (int i = 1; i <= test_case; i++)
	{
		int n;
		//int arr[10] = { false };
		int check = 0;

		std::cin >> n;

		int answer = n;
		int temp = answer;

		while (true)
		{

			while (temp)
			{
				check |= 1 << (temp % 10);
				//if (!arr[temp % 10])
				//{
				//	arr[temp % 10] = true;
				//	check++;
				//}
				temp /= 10;

			}


			if (check == (1 << 10) - 1)
			{
				std::cout << "#" << i << " " << answer << std::endl;
				break;
			}
			answer += n;
			temp = answer;


		}





	}
}