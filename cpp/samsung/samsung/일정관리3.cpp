#if 0
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

typedef enum {
	INIT,
	ADD,
	DELETE,
	CHANGE,
	GETCOUNT
} COMMAND;

extern void init();
extern void addEvent(int uid, char ename[], int groupid);
extern int deleteEvent(int uid, char ename[]);
extern int changeEvent(int uid, char ename[], char cname[]);
extern int getCount(int uid);

/////////////////////////////////////////////////////////////////////////
#include <unordered_map>
#include <string>

struct Memo {
	int mygroup;
	int isalive;
	bool ismaster;
	Memo* master;
	int child[4];
	int child_count;

	void clear() {
		for (int i = 0; i < 4; i++) {
			child[i] = -1;
		}
		child_count = 0;
	}

	void childpush(int a) {
		for (int i = 0; i < 4; ++i) {
			if (child[i] != -1) continue;
			child[i] = a;
			break;
		}
		++child_count;
	}

	void childpop(int a) {
		for (int i = 0; i < 4; ++i) {
			if (child[i] != a) continue;
			child[i] = -1;
			break;
		}
		--child_count;
	}
}memo[50000];

Memo* isthere[50000];
int user[1000];
int isthere_count;
int memo_count;

std::unordered_map<std::string, int> memo_map[100];
std::unordered_map<std::string, int> user_map[1000];

void init(){
	for (int i = 0; i < 1000; ++i) {
		user[i] = 0;
		user_map[i].clear();
	}
	for(int i = 0; i<100; ++i) memo_map[i].clear();
	for (int i = 0; i < 50000; ++i) isthere[i] = 0;

	isthere_count = 0;
	memo_count = 0;
	
}

void addEvent(int uid, char ename[], int groupid){
	
	int memoidx = memo_count++;
	user_map[uid][ename] = memoidx;
	memo[memoidx].mygroup = groupid;
	memo[memoidx].clear();

	// 해당 그룹에 ename이 새로 생성 되거나, 
	// 생성 되었더라도, erase되어서 포인터가 없다면
	// 이 글이 마스터
	if (memo_map[groupid].find(ename) == memo_map[groupid].end() ||
		isthere[memo_map[groupid][ename]] == 0)
	{
		memo_map[groupid][ename] = isthere_count;
		isthere[isthere_count] = &memo[memoidx];
		memo[memoidx].isalive = isthere_count++;
		memo[memoidx].ismaster = true;
	}
	else {
		memo[memoidx].ismaster = false;
		memo[memoidx].master = isthere[memo_map[groupid][ename]];
		memo[memoidx].master->childpush(uid);
	}

	++user[uid];

}

int deleteEvent(int uid, char ename[])
{
	--user[uid];
	int memoidx = user_map[uid][ename];
	
	if (memo[memoidx].ismaster) {
		isthere[memo[memoidx].isalive] = 0;
		for (int i = 0; i < 4; ++i) {
			if (memo[memoidx].child[i] == -1) continue;
			--user[memo[memoidx].child[i]];
		}
		return memo[memoidx].child_count + 1;
	}

	memo[memoidx].master->childpop(uid);
	return 1;
}

int changeEvent(int uid, char ename[], char cname[])
{
	int memoidx = user_map[uid][ename];
	user_map[uid][cname] = memoidx;
	user_map[uid].erase(ename);

	if (memo[memoidx].ismaster) {
		for (int i = 0; i < 4; ++i) {
			int child_write_uid = memo[memoidx].child[i];
			if (child_write_uid == -1) continue;

			user_map[child_write_uid][cname] = user_map[child_write_uid][ename];
			user_map[child_write_uid].erase(ename);
		}
		memo_map[memo[memoidx].mygroup][cname] = memo_map[memo[memoidx].mygroup][ename];
		memo_map[memo[memoidx].mygroup].erase(ename);

		return memo[memoidx].child_count + 1;
	}

	memo[memoidx].master->childpop(uid);

	memo[memoidx].clear();
	memo_map[memo[memoidx].mygroup][cname] = isthere_count;
	isthere[isthere_count] = &memo[memoidx];
	memo[memoidx].isalive = isthere_count++;
	memo[memoidx].ismaster = true;

	return 1;
}

int getCount(int uid)
{
	return user[uid];
}

/////////////////////////////////////////////////////////////////////////

static int mSeed;
static int pseudo_rand(void)
{
	mSeed = mSeed * 431345 + 2531999;
	return mSeed & 0x7FFFFFFF;
}

static void make_string(char str[], int seed)
{
	mSeed = seed;
	int length = 5 + pseudo_rand() % 10;
	for (int i = 0; i < length; ++i) {
		str[i] = 'a' + pseudo_rand() % 26;
	}
	str[length] = 0;
}

static int run()
{
	int answer = 100;

	int cmd, p1, p2, p3, p4;
	char str1[15], str2[15];

	int N, ret, flag;
	scanf("%d %d %d", &cmd, &N, &flag);

	init();

	for (int i = 1; i < N; ++i) {
		scanf("%d", &cmd);
		switch (cmd) {
		case ADD:
			if (flag == 1) {
				scanf("%d %s %d", &p1, str1, &p3);
			}
			else {
				scanf("%d %d %d", &p1, &p2, &p3);
				make_string(str1, p2);
			}
			addEvent(p1, str1, p3);
			break;

		case DELETE:
			if (flag == 1) {
				scanf("%d %s %d", &p1, str1, &p3);
			}
			else {
				scanf("%d %d %d", &p1, &p2, &p3);
				make_string(str1, p2);
			}
			ret = deleteEvent(p1, str1);
			if (ret != p3)
				answer = 0;
			break;

		case CHANGE:
			if (flag == 1) {
				scanf("%d %s %s %d", &p1, str1, str2, &p4);
			}
			else {
				scanf("%d %d %d %d", &p1, &p2, &p3, &p4);
				make_string(str1, p2);
				make_string(str2, p3);
			}
			ret = changeEvent(p1, str1, str2);
			if (ret != p4)
				answer = 0;
			break;

		case GETCOUNT:
			scanf("%d %d", &p1, &p2);
			ret = getCount(p1);
			if (ret != p2)
				answer = 0;
			break;

		default:
			break;
		}
	}

	return answer;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("일정관리3.txt", "r", stdin);

	int T;
	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++) {
		printf("#%d %d\n", tc, run());
	}

	return 0;
}
#endif