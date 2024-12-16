#if 0
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>

using namespace std;

const int MAXN = 100000;

extern int FindAnagram(int Len1, char *S1, int Len2, char *S2);

char S1[MAXN + 5];
char S2[MAXN + 5];

int main(void) {
	setbuf(stdout, NULL);
	//freopen("아나그램_input.txt", "r", stdin);

	int TestCase; for (scanf("%d", &TestCase); TestCase--;) {

		scanf("%s", S1);
		scanf("%s", S2);

		//L1 = Length of S1, L2 = Length of S2
		int L1 = 0, L2 = 0;
		for (; S1[L1]; L1++);
		for (; S2[L2]; L2++);

		int answer = FindAnagram(L1, S1, L2, S2);

		static int tc = 0;
		printf("#%d %d\n", ++tc, answer);
	}
	return 0;
}

int count_S1[26];
int count_S2[26];

bool check() {
	for (int i = 0; i < 26; ++i) {
		if (count_S1[i] != count_S2[i]) return false;
	}
	return true;
}

int FindAnagram(int Len1, char *S1, int Len2, char *S2) {

	for (int i = 0; i < 26; ++i) {
		count_S1[i] = 0;
		count_S2[i] = 0;
	}

	for (int i = 0; i < Len1; ++i){
		++count_S1[S1[i] - 'a'];
		++count_S2[S2[i] - 'a'];
	}
	
	int answer = 0;
	if (check()) ++answer;

	for (int i = Len1; i < Len2; ++i) {
		++count_S2[S2[i] - 'a'];
		--count_S2[S2[i - Len1] - 'a'];
		if (check()) ++answer;
	}


	return answer;
}
#endif