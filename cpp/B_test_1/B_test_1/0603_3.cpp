#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

struct node
{
	int value;
	struct node* next = NULL;
};

int min(int a,int b)
{
	if (a < b)
		return a;
	else
		return b;
}

int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

void solve()
{
	int n;
	std::cin >> n;

	struct node *head = NULL;
	struct node *tail = NULL;

	//초기 암호문 입력받기
	for (int i = 0; i < n; i++) {
		node* new_node = new node;
		std::cin >> new_node->value;

		if (head == NULL)
		{
			head = new_node;
			tail = new_node;
		}
		else
		{
			tail->next = new_node;
			tail = new_node;
		}
	}

	//명령의 개수 입력받기
	int count_order;
	std::cin >> count_order;

	// 각명령에 대해서
	for (int i = 0; i < count_order; i++)
	{
		char order;
		std::cin >> order;

		//삽입
		if (order == 'I')
		{
			int x, y;
			std::cin >> x >> y;

			n += y;

			if (x == 0)
			{
				node* new_node = new node;
				std::cin >> new_node->value;

				new_node->next = head;
				head = new_node;

				node* insert_point = head;

				for (int j = 0; j < y-1; j++) {
					node* new_node = new node;
					std::cin >> new_node->value;

					if (head == NULL)
					{
						head = new_node;
						tail = new_node;
					}
					else {
						new_node->next = insert_point->next;
						insert_point->next = new_node;
						insert_point = new_node;

					}
				}

				continue;
			}
		
			


			node* insert_point = head;

			for (int j = 1; j < x; j++) {
				insert_point = insert_point->next;
			}

			for (int j = 0; j < y; j++) {
				node* new_node = new node;
				std::cin >> new_node->value;

				if (head == NULL)
				{
					head = new_node;
					tail = new_node;
				}
				else {
					new_node->next = insert_point->next;
					insert_point->next = new_node;
					insert_point = new_node;

				}
			}
		}

		//삭제
		else if (order == 'D')
		{
			int x, y;
			std::cin >> x >> y;

			n -= y;

			node* delete_point = head;
			
			for (int j = 1; j < x; j++) {
				delete_point = delete_point->next;
			}


			for (int j = 0; j < y; j++)
			{
				node* delete_node = delete_point->next;
				delete_point->next = delete_point->next->next;
				delete delete_node;
			}

			if (x == n) tail = delete_point;

		}

		//추가
		else if (order == 'A')
		{
			int y;
			std::cin >> y;

			n += y;

			for (int j = 0; j < y; j++) {
				node* new_node = new node;
				std::cin >> new_node->value;

				if (head == NULL)
				{
					head = new_node;
					tail = new_node;
				}
				else
				{
					tail->next = new_node;
					tail = new_node;
				}
			}
		}
	}
	
	n = min(10, n);

	for (int i = 0; i < n; i++) {
		std::cout << head->value << " ";
		head = head->next;
	}

	std::cout << "\n";


}


int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	//파일을 입력으로 받기
	freopen("input_0603_3.txt", "r", stdin);


	for (int test_case = 1; test_case <= 10; test_case++)
	{
		std::cout << "#" << test_case << " ";
		solve();
	}
	


	return 0;
}