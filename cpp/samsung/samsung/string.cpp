#if 0
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>

char string[1000];
int string_size;
char findchar[10];
int find_size;
int failure[10];

int solve() {
	//tc번호 입력 받기
	char temp = '\0';
	while (1) {
		std::cin.get(temp);
		if (temp == '\n') break;
	}
	find_size = 0;
	while (1) {
		std::cin.get(findchar[find_size]);
		if (findchar[find_size++] == '\n') break;
	}
	--find_size;

	string_size = 0;
	while (1) {
		std::cin.get(string[string_size]);
		if(string[string_size++] == '\n') break;
 	}
	--string_size;

	failure[0] = 0;
	int i = 1;
	int j = 0;

	while (i < find_size) {
		if (findchar[i] == findchar[j]) failure[i++] = ++j;
		else if (j) j = failure[j - 1];
		else failure[i++] = 0;
	}

	j = 0;
	int answer = 0;

	for (int i = 0; i < string_size; ++i) {
		while (j > 0 && string[i] != findchar[j]) {
			j = failure[j - 1];
		}
		if (string[i] == findchar[j]) {
			j++;
		}
		if (j == find_size) {
			++answer; 
			j = failure[j - 1]; 		}
	}

	return answer;

}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	freopen("string_input.txt", "r", stdin);

	for (int tc = 1; tc <= 10; ++tc) {
		std::cout << "#" << tc << " " << solve() << "\n";
	}

}
#endif