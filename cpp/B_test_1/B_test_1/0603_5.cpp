#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 1
#define CMD_HIRE 2
#define CMD_FIRE 3
#define CMD_UPDATE_SOLDIER 4
#define CMD_UPDATE_TEAM 5
#define CMD_BEST_SOLDIER 6

extern void init();
extern void hire(int mID, int mTeam, int mScore);
extern void fire(int mID);
extern void updateSoldier(int mID, int mScore);
extern void updateTeam(int mTeam, int mChangeScore);
extern int bestSoldier(int mTeam);

/////////////////////////////////////////////////////////////////////////

#include <vector>

struct soldier_node {
	soldier_node* before;
	soldier_node* after;
	
	int mID;
	int mTeam;
	int mScore;
};

struct linked_list {
	soldier_node* head;
	soldier_node* tail;
};

soldier_node* soldier[100000] = { NULL };
std::vector< std::vector <linked_list>> team_score(5);

int min(int a, int b)
{
	if (a > b) return b;
	return a;
}

int max(int a, int b)
{
	if (a > b) return a;
	return b;
}

//bool check()
//{
//	for (int i = 0; i < 5; i++)
//	{
//		for (int j = 0; j < 5; j++)
//		{
//			if (team_score[i][j].head != NULL && team_score[i][j].tail == NULL)
//				return true;
//		}
//	}
//	return false;
//}

void init()
{
	for (int i = 0; i < 100000; i++) {
		if (soldier[i] != NULL) {
			delete soldier[i];
			soldier[i] = NULL;
		}
	}

	for (int i = 0; i < 5; i++) {
		team_score[i].clear();
		std::vector<linked_list> scores;
		for (int j = 0; j < 5; j++) {
			linked_list temp;
			temp.head = NULL;
			temp.tail = NULL;
			scores.push_back(temp);
		}
		team_score[i] = scores;
	}

	//check();
}

void hire(int mID, int mTeam, int mScore)
{
	soldier_node* new_soldier = new soldier_node;
	new_soldier->mID = mID;
	new_soldier->mTeam = mTeam;
	new_soldier->mScore = mScore;
	new_soldier->after = NULL;
	new_soldier->before = NULL;

	if (team_score[mTeam - 1][mScore - 1].head == NULL)
	{
		team_score[mTeam - 1][mScore - 1].head = new_soldier;
		team_score[mTeam - 1][mScore - 1].tail = new_soldier;

	}
	else
	{
		new_soldier->before = team_score[mTeam - 1][mScore - 1].tail;
		team_score[mTeam - 1][mScore - 1].tail->after = new_soldier;
		team_score[mTeam - 1][mScore - 1].tail = new_soldier;
	}


	soldier[mID - 1] = new_soldier;

	//check();
}

void fire(int mID)
{
	int mTeam = soldier[mID - 1]->mTeam;
	// 기존의 방식에서 점수의 업데이트를 리스트로 옮긴다면 mScore는 갱신 되지 않는다.
	// 하지만 해당 변수는 mID의 병사가 head or tail인 경우에만 사용하므로 head or tail로 배정될때 mScore를 갱신 해준다.
	int mScore = soldier[mID - 1]->mScore;

	// 원래 있던 링크드 리스트에서 제거함

	// 자기 자신만 있었다면, 헤드와 꼬리를 없앰
	if (soldier[mID - 1]->before == NULL && soldier[mID - 1]->after == NULL)
	{
		team_score[mTeam - 1][mScore - 1].head = NULL;
		team_score[mTeam - 1][mScore - 1].tail = NULL;
	}
	// 자신이 헤드였으면 다음 노드의 before는 비우고, 헤드를 바꿈
	else if (soldier[mID - 1]->before == NULL)
	{
		soldier[mID - 1]->after->before = NULL;
		team_score[mTeam - 1][mScore - 1].head = soldier[mID - 1]->after;
		team_score[mTeam - 1][mScore - 1].head->mScore = mScore;
	}

	// 자신이 꼬리였으면, 이전 노드의 after을 비우고, 꼬리를 바꿈
	else if (soldier[mID - 1]->after == NULL)
	{
		soldier[mID - 1]->before->after = NULL;
		team_score[mTeam - 1][mScore - 1].tail = soldier[mID - 1]->before;
		team_score[mTeam - 1][mScore - 1].tail->mScore = mScore;
	}

	// 그 외에는 앞과 뒤를 연결 해줌
	else
	{
		soldier[mID - 1]->before->after = soldier[mID - 1]->after;
		soldier[mID - 1]->after->before = soldier[mID - 1]->before;
	}


	delete soldier[mID - 1];
	soldier[mID - 1] = NULL;

	//check();
}

void updateSoldier(int mID, int mScore)
{
	int mTeam = soldier[mID - 1]->mTeam;
	// 기존의 방식에서 점수의 업데이트를 리스트로 옮긴다면 mScore는 갱신 되지 않는다.
	// 하지만 해당 변수는 mID의 병사가 head or tail인 경우에만 사용하므로 head or tail로 배정될때 mScore를 갱신 해준다.
	int before_mScore = soldier[mID - 1]->mScore;

	//기존 링크드 리스트에서 없애줌
	if (soldier[mID - 1]->before == NULL && soldier[mID - 1]->after == NULL)
	{
		team_score[mTeam - 1][before_mScore - 1].head = NULL;
		team_score[mTeam - 1][before_mScore - 1].tail = NULL;

	}
	else if (soldier[mID - 1]->before == NULL)
	{
		soldier[mID - 1]->after->before = NULL;
		team_score[mTeam - 1][before_mScore - 1].head = soldier[mID - 1]->after;
		team_score[mTeam - 1][before_mScore - 1].head->mScore = before_mScore;
	}

	else if (soldier[mID - 1]->after == NULL)
	{
		soldier[mID - 1]->before->after = NULL;
		team_score[mTeam - 1][before_mScore - 1].tail = soldier[mID - 1]->before;
		team_score[mTeam - 1][before_mScore - 1].tail->mScore = before_mScore;
	}

	else
	{
		soldier[mID - 1]->before->after = soldier[mID - 1]->after;
		soldier[mID - 1]->after->before = soldier[mID - 1]->before;
	}

	//새로운 평점의 링크드 리스트에 추가
	if (team_score[mTeam - 1][mScore - 1].head == NULL)
	{
		team_score[mTeam - 1][mScore - 1].head = soldier[mID - 1];
		team_score[mTeam - 1][mScore - 1].tail = soldier[mID - 1];
		soldier[mID - 1]->before = NULL;

	}
	else
	{
		soldier[mID - 1]->before = team_score[mTeam - 1][mScore - 1].tail;
		team_score[mTeam - 1][mScore - 1].tail->after = soldier[mID - 1];
		team_score[mTeam - 1][mScore - 1].tail = soldier[mID - 1];
	}

	soldier[mID - 1]->after = NULL;
	soldier[mID - 1]->mScore = mScore;

	//check();
}

void updateTeam(int mTeam, int mChangeScore)
{
	if (mChangeScore == 0) return;

	if (mChangeScore < 0)
	{
		for (int i = 1; i < 5; i++)
		{
			int target_score = max(0, i + mChangeScore);

			//현재 점수의 인원이 비었으면 다음 반복
			if (team_score[mTeam - 1][i].head == NULL) continue;

			//타겟이 비어있으면
			if (team_score[mTeam - 1][target_score].head == NULL)
			{
				team_score[mTeam - 1][target_score] = team_score[mTeam - 1][i];
				//mScore가 실제로 바뀌지 않기때문에 문제가 생길수 있다.
				// 하지만 해당 병사가 head or tail이 되는 경우에 mScore를 사용하므로 head and tail의 병사 mScore만 갱신 해준다.
				team_score[mTeam - 1][target_score].head->mScore = target_score + 1;
				team_score[mTeam - 1][target_score].tail->mScore = target_score + 1;

				team_score[mTeam - 1][i].head = NULL;
				team_score[mTeam - 1][i].tail = NULL;
				continue;
			}

			//그 외에 실제로 연결하는 경우
			team_score[mTeam - 1][i].head->before = team_score[mTeam - 1][target_score].tail;
			team_score[mTeam - 1][target_score].tail->after = team_score[mTeam - 1][i].head;
			team_score[mTeam - 1][target_score].tail = team_score[mTeam - 1][i].tail;

			team_score[mTeam - 1][target_score].tail->mScore = target_score + 1;

			team_score[mTeam - 1][i].head = NULL;
			team_score[mTeam - 1][i].tail = NULL;

		}
	}
	else if (mChangeScore > 0)
	{
		for (int i = 3; i > -1; i--)
		{
			int target_score = min(4, i + mChangeScore);

			//현재 점수의 인원이 비었으면 다음 반복
			if (team_score[mTeam - 1][i].head == NULL) continue;

			//타겟이 비어있으면
			if (team_score[mTeam - 1][target_score].head == NULL)
			{
				team_score[mTeam - 1][target_score] = team_score[mTeam - 1][i];

				team_score[mTeam - 1][target_score].head->mScore = target_score + 1;
				team_score[mTeam - 1][target_score].tail->mScore = target_score + 1;

				team_score[mTeam - 1][i].head = NULL;
				team_score[mTeam - 1][i].tail = NULL;
				continue;
			}

			team_score[mTeam - 1][i].head->before = team_score[mTeam - 1][target_score].tail;
			team_score[mTeam - 1][target_score].tail->after = team_score[mTeam - 1][i].head;
			team_score[mTeam - 1][target_score].tail = team_score[mTeam - 1][i].tail;

			team_score[mTeam - 1][target_score].tail->mScore = target_score + 1;

			team_score[mTeam - 1][i].head = NULL;
			team_score[mTeam - 1][i].tail = NULL;

		}
	}

	//check();
}

int bestSoldier(int mTeam)
{
	for (int score = 4; score > -1; score--)
	{
		if (team_score[mTeam - 1][score].head == NULL) continue;

		soldier_node* temp = team_score[mTeam - 1][score].head;
		int return_value = temp->mID;

		while (true)
		{
			if (temp->after == NULL) break;

			temp = temp->after;
			return_value = max(return_value, temp->mID);
		}

		return return_value;

	}

	return 0;
}
/////////////////////////////////////////////////////////////////////////

static bool run()
{
	int numQuery;

	int mID, mTeam, mScore, mChangeScore;

	int userAns, ans;

	bool isCorrect = false;

	scanf("%d", &numQuery);

	for (int i = 0; i < numQuery; ++i)
	{

		int cmd;
		scanf("%d", &cmd);
		switch (cmd)
		{
		case CMD_INIT:
			init();
			isCorrect = true;
			break;
		case CMD_HIRE:
			scanf("%d %d %d", &mID, &mTeam, &mScore);
			hire(mID, mTeam, mScore);
			break;
		case CMD_FIRE:
			scanf("%d", &mID);
			fire(mID);
			break;
		case CMD_UPDATE_SOLDIER:
			scanf("%d %d", &mID, &mScore);
			updateSoldier(mID, mScore);
			break;
		case CMD_UPDATE_TEAM:
			scanf("%d %d", &mTeam, &mChangeScore);
			updateTeam(mTeam, mChangeScore);
			break;
		case CMD_BEST_SOLDIER:
			scanf("%d", &mTeam);
			userAns = bestSoldier(mTeam);
			scanf("%d", &ans);
			if (userAns != ans)
			{
				isCorrect = false;
			}
			break;
		default:
			isCorrect = false;
			break;
		}
	}

	return isCorrect;
}



int main()
{
	setbuf(stdout, NULL);
	freopen("input_0603_5.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}