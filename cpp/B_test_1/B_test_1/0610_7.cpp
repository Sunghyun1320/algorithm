#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>

struct Node {
	char value;
	int left;
	int right;
};


void inorder(std::vector<Node*> tree, Node* alpha)
{
	if (alpha->left != 0)
		inorder(tree, tree[alpha->left]);

	std::cout << alpha->value;

	if (alpha->right != 0)
		inorder(tree, tree[alpha->right]);

}

void solve(int test_case)
{
	int n;
	std::cin >> n;
	std::cin.ignore();

	std::vector<Node*> tree(n + 1);

	for (int i = 0; i < n; i++)
	{
		Node* temp = new Node;
		temp->left = 0;
		temp->right = 0;


		std::string input_data;

		std::getline(std::cin, input_data);
		input_data += " ";

		int data_num = 0;
		int data = 0;
		for (int i = 0; i < input_data.length(); i++)
		{
			char char_ = input_data[i];
			if (char_ == ' ')
			{
				switch (data_num)
				{
				case 0:
					tree[data] = temp;
					break;
				case 1:
					temp->value = char(data + '0');
					break;
				case 2:
					temp->left = data;
					break;
				case 3:
					temp->right = data;
					break;

				default:
					break;
				}

				data_num += 1;
				data = 0;
				continue;
			}

			data *= 10;
			data += char_ - '0';


		}







	}

	std::cout << "#" << test_case << " ";
	inorder(tree, tree[1]);
	std::cout << "\n";
}



int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	freopen("input_0610_2.txt", "r", stdin);


	int T = 10;



	for (int test_case = 1; test_case <= T; test_case++)
	{
		solve(test_case);
	}



	return 0;
}