#if 0
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>

using namespace std;

const int MAXN = 500000;
const int MAXM = 100000;

extern int FindString(int N, char *A, int M, char *B);

char A[MAXN + 5];
char B[MAXM + 5];

int main(void) {
	setbuf(stdout, NULL);
	freopen("단어가 등장하는 횟수_input.txt", "r", stdin);

	int TestCase; for (scanf("%d", &TestCase); TestCase--;) {

		scanf("%s", A);
		scanf("%s", B);

		//N = Length of A, M = Length of B
		int N = 0, M = 0;
		for (; A[N]; N++);
		for (; B[M]; M++);

		int answer = FindString(N, A, M, B);

		static int tc = 0;
		printf("#%d %d\n", ++tc, answer);
	}
	return 0;
}

////////////////////////////////////////////////////
int failure[100000];

int FindString(int N, char *A, int M, char *B) {
	failure[0] = 0;
	int i = 1;
	int j = 0;
	
	while (i < M) {
		if (B[i] == B[j]) failure[i++] = ++j;
		else if (j) j = failure[j - 1];
		else failure[i++] = 0;
	}

	j = 0;
	int answer = 0;

	for (int i = 0; i < N; ++i) {
		while (j > 0 && A[i] != B[j]) {
			j = failure[j - 1];
		}
		if (A[i] == B[j]) {
			j++;
		}
		if (j == M) {
			++answer;
			j = failure[j - 1];
		}
	}

	return answer;
}
#endif