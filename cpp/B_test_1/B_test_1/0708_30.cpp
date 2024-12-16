#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <map>

struct Trie {
	bool is_end;
	char alphabet;
	int count;
	std::map<char, Trie*> children;

	Trie(char alpha) : alphabet(alpha), is_end(false), count(0) {};

	Trie() : alphabet('\0'), is_end(false), count(0) {};
};

int K;

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	freopen("input_0708_30.txt", "r", stdin);

	int T;
	std::cin >> T;

	for (int test_case = 1; test_case <= T; test_case++)
	{
		std::cin >> K;
		std::string words;
		std::cin >> words;
		int len = words.length();

		if (K > len)
		{
			std::cout << "#" << test_case << " none\n";
			continue;
		}


	}



	return 0;
}