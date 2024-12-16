#if 0
#if 1
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT				(100)
#define CMD_WRITE_MESSAGE		(200)
#define CMD_COMMENT_TO			(300)
#define CMD_ERASE				(400)
#define CMD_GET_BEST_MESSAGES	(500)
#define CMD_GET_BEST_USERS		(600)

#define MAXL	(10)	

extern void init();
extern int writeMessage(char mUser[], int mID, int mPoint);
extern int commentTo(char mUser[], int mID, int mTargetID, int mPoint);
extern int erase(int mID);
extern void getBestMessages(int mBestMessageList[]);
extern void getBestUsers(char mBestUserList[][MAXL + 1]);

static int mstrcmp(char a[], char b[])
{
	int idx = 0;
	while (a[idx] != '\0' && a[idx] == b[idx])
		++idx;
	return a[idx] - b[idx];
}

static bool run()
{
	int Q;
	int mID, mTargetID, mPoint;
	char mUser[MAXL + 1];
	char mBestUserList[5][MAXL + 1];
	int mBestMessageList[5];

	int ret = -1, ans;

	scanf("%d", &Q);

	bool okay = false;

	for (int q = 0; q < Q; ++q)
	{
		int cmd;
		scanf("%d", &cmd);
		switch (cmd)
		{
		case CMD_INIT:
			init();
			okay = true;
			break;
		case CMD_WRITE_MESSAGE:
			scanf("%s %d %d", mUser, &mID, &mPoint);
			ret = writeMessage(mUser, mID, mPoint);
			scanf("%d", &ans);
			if (ret != ans)
				okay = false;
			break;
		case CMD_COMMENT_TO:
			scanf("%s %d %d %d", mUser, &mID, &mTargetID, &mPoint);
			ret = commentTo(mUser, mID, mTargetID, mPoint);
			scanf("%d", &ans);
			if (ret != ans)
				okay = false;
			break;
		case CMD_ERASE:
			scanf("%d", &mID);
			ret = erase(mID);
			scanf("%d", &ans);
			if (ret != ans)
				okay = false;
			break;
		case CMD_GET_BEST_MESSAGES:
			getBestMessages(mBestMessageList);
			for (int i = 0; i < 5; ++i)
			{
				scanf("%d", &ans);
				if (mBestMessageList[i] != ans)
					okay = false;
			}
			break;
		case CMD_GET_BEST_USERS:
			getBestUsers(mBestUserList);
			for (int i = 0; i < 5; ++i)
			{
				scanf("%s", mUser);
				if (mstrcmp(mBestUserList[i], mUser) != 0)
					okay = false;
			}
			break;
		default:
			okay = false;
			break;
		}
	}

	return okay;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("전자게시판.txt", "r", stdin);

	int TC, MARK;

	scanf("%d %d", &TC, &MARK);
	for (int tc = 1; tc <= TC; ++tc)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}
#endif
/////////////////////////////////////////////////////
#define MAXL	(10)
#include <unordered_map>
#include <string>

template<typename T>
struct Stack {
	T* data;
	int size;
	int capasity;

	Stack(int init_capa = 2) :size(0), capasity(init_capa) {
		data = new T[init_capa];
	}

	~Stack() {
		delete[] data;
	}

	void clear() {
		size = 0;
	}

	void resize(int new_capa) {
		T* new_data = new T[new_capa];
		for (int i = 0; i < size; ++i) {
			new_data[i] = data[i];
		}
		delete[] data;
		data = new_data;
		capasity = new_capa;
	}

	void push(T value) {
		if (size == capasity) resize(capasity * 2);

		data[size++] = value;
	}

	T pop() {
		return data[--size];
	}

	T operator[](int index) {
		return data[index];
	}

};

template<typename T>
struct Heap {
	T* data;
	int size;
	int capasity;

	Heap(int init_capa = 2) :size(0), capasity(init_capa) {
		data = new T[init_capa];
	}

	~Heap() {
		delete[] data;
	}

	void clear() {
		size = 0;
	}
	void resize(int new_capa) {
		T* new_data = new T[new_capa];
		for (int i = 0; i < size; ++i) {
			new_data[i] = data[i];
		}
		delete[] data;
		data = new_data;
		capasity = new_capa;
	}

	void upswap(int child) {
		T value = data[child];

		while (child > 0) {
			int paridx = (child - 1) >> 1;
			T par = data[paridx];

			if (*value < *par) {
				data[child] = par;
				// 요소 자체에 heap index를 저장하기 위함
				// T자체에 index는 반드시 있을 예정이며,
				// 포인터로 힙을 생성예정
				par->index = child;
				child = paridx;
				continue;
			}

			break;
		}

		data[child] = value;
		value->index = child;
	}

	void downswap(int par) {
		T value = data[par];

		int child = (par << 1) + 1;

		while (child < size) {
			int right = child + 1;
			if (right < size && !(*data[child] < *data[right])) child = right;

			if (*data[child] < *value) {
				data[par] = data[child];
				// 요소 자체에 heap index를 저장하기 위함
				// T자체에 index는 반드시 있을 예정이며,
				// 포인터로 힙을 생성예정
				data[par]->index = par;
				par = child;
				child = (par << 1) + 1;
				continue;
			}

			break;
		}

		data[par] = value;
		data[par]->index = par;
	}

	void push(T value) {
		if (size == capasity) resize(capasity * 2);

		data[size++] = value;
		upswap(size-1);
	}

	T pop() {
		if(size == 0 ){/*error*/ }

		T returnvalue = data[0];
		data[0] = data[--size];
		data[0]->index = 0;
		downswap(0);

		return returnvalue;
	}
};

struct User {
	int index;
	char name[MAXL + 1];
	int point;

	
	bool operator<(const User& other) {
		if (point != other.point) {
			//최대힙을 위한 부호 반대.
			return point > other.point;
		}

		for (int i = 0; i < 10; ++i) {
			if (name[i] == other.name[i]) continue;
			return name[i] < other.name[i];
		}
		
	}
}user[10000];

struct Message {
	int index;
	int mid;
	int point;
	int sum_point;
	int par;
	int useridx;
	Stack<int> child;

	bool operator<(const Message& other) {
		if (sum_point == other.sum_point) return mid < other.mid;
		//최대힙을 위한 부호 반대
		return sum_point > other.sum_point;
	}

}message[100000];

int count_user;
int count_message;

std::unordered_map<int, int> map_message;
std::unordered_map<std::string, int> map_user;

Heap<User*> heap_user;
Heap<Message*> heap_message;

void init()
{
	count_user = 0;
	count_message = 0;
	map_message.clear();
	map_user.clear();
	heap_user.clear();
	heap_message.clear();

	return;
}

int writeMessage(char mUser[], int mID, int mPoint)
{
	int useridx = 0;

	//이미 있는 유저인 경우
	if (map_user.find(mUser) != map_user.end()) {
		useridx = map_user[mUser];
	}
	//없는 유저인 경우
	else {
		map_user[mUser] = count_user;
		useridx = count_user++;
		user[useridx].point = 0;
		for (int i = 0; i < MAXL + 1; ++i) {
			user[useridx].name[i] = mUser[i];
			if (mUser[i] == '\0') break;
		}
		heap_user.push(&user[useridx]);
	}

	//새로운 메세지 생성후 heappush
	map_message[mID] = count_message;
	message[count_message].mid = mID;
	message[count_message].point = mPoint;
	message[count_message].sum_point = mPoint;
	message[count_message].par = -1;
	message[count_message].useridx = useridx;
	message[count_message].child.clear();
	heap_message.push(&message[count_message++]);

	//유저 점수 갱신 후 heap업데이트
	user[useridx].point += mPoint;
	heap_user.upswap(user[useridx].index);
	heap_user.downswap(user[useridx].index);

	return user[useridx].point;
}										  

int commentTo(char mUser[], int mID, int mTargetID, int mPoint)
{
	int useridx = 0;

	//이미 있는 유저인 경우
	if (map_user.find(mUser) != map_user.end()) {
		useridx = map_user[mUser];
	}
	//없는 유저인 경우
	else {
		map_user[mUser] = count_user;
		useridx = count_user++;
		user[useridx].point = 0;
		for (int i = 0; i < MAXL + 1; ++i) {
			user[useridx].name[i] = mUser[i];
			if (mUser[i] == '\0') break;
		}
		heap_user.push(&user[useridx]);
	}

	int targetidx = map_message[mTargetID];

	//새로운 메세지 생성후 heappush
	map_message[mID] = count_message;
	message[count_message].mid = mID;
	message[count_message].point = mPoint;
	message[count_message].sum_point = mPoint;
	message[count_message].par = targetidx;
	message[count_message].useridx = useridx;
	message[count_message].child.clear();
	//heap_message.push(&message[count_message]);

	////타겟 메세지 점수 갱신 후 heap업데이트
	//message[targetidx].sum_point += mPoint;
	//heap_message.upswap(message[targetidx].index);
	//heap_message.downswap(message[targetidx].index);
	// 타겟 글에 자식으로 본인 추가
	message[targetidx].child.push(count_message++);

	// 타겟이 원글이 아닌경우(댓글인 경우) 원글 점수 갱신
	if (message[targetidx].par != -1) {
		targetidx = message[targetidx].par;
	}

	//원글 점수 갱신 후 heap업데이트
	message[targetidx].sum_point += mPoint;
	heap_message.upswap(message[targetidx].index);
	heap_message.downswap(message[targetidx].index);
	
	//유저 점수 갱신 후 heap업데이트
	user[useridx].point += mPoint;
	heap_user.upswap(user[useridx].index);
	heap_user.downswap(user[useridx].index);

	return message[targetidx].sum_point;
}

int erase(int mID)
{
	int messageidx = map_message[mID];

	Stack<int> dfs;
	dfs.push(messageidx);
	int remove_point = 0;

	while (dfs.size) {
		int now = dfs.pop();
		remove_point += message[now].point;

		//유저의 포인트 삭제후 heap갱신
		user[message[now].useridx].point -= message[now].point;
		heap_user.upswap(user[message[now].useridx].index);
		heap_user.downswap(user[message[now].useridx].index);

		//메세지 삭제 표시로point -1적용
		//heap구조에서 최 후미로 보내기 위함
		message[now].sum_point = -1;
		if (message[now].par == -1) {
			heap_message.downswap(message[now].index);
			heap_message.upswap(message[now].index);
		}

		for (int i = 0; i< message[now].child.size; ++i) {
			if (message[message[now].child[i]].sum_point == -1) continue;
			dfs.push(message[now].child[i]);
		}
	}

	
	//글일 경우 작성자의 포인트 반환.
	if (message[messageidx].par == -1) return user[message[messageidx].useridx].point;

	
	//// 댓글 혹은 답글일경우 원글의 포인트 변경,
	//message[message[messageidx].par].sum_point -= message[message[messageidx].par].sum_point;
	//heap_message.downswap(message[message[messageidx].par].index);

	//if (message[message[messageidx].par].par == -1) return message[message[messageidx].par].sum_point;

	//답글일 경우 원글의 포인트 변경까지
	if (message[message[messageidx].par].par != -1) messageidx = message[messageidx].par;

	//messageidx = message[messageidx].par;
	message[message[messageidx].par].sum_point -= remove_point;
	heap_message.downswap(message[message[messageidx].par].index);

	return message[message[messageidx].par].sum_point;
}

void getBestMessages(int mBestMessageList[])
{
	Message* temp[5];
	for (int i = 0; i < 5; i++) {
		temp[i] = heap_message.pop();
		mBestMessageList[i] = temp[i]->mid;
	}

	for (int i = 0; i < 5; i++) {
		heap_message.push(temp[i]);
	}
	return;
}

void getBestUsers(char mBestUserList[][MAXL + 1])
{
	User* temp[5];
	for (int i = 0; i < 5; i++) {
		temp[i] = heap_user.pop();
		for (int j = 0; j < MAXL + 1; j++) {
			mBestUserList[i][j] = temp[i]->name[j];
			if (mBestUserList[i][j] == '\0') break;
		}
	}

	for (int i = 0; i < 5; i++) {
		heap_user.push(temp[i]);
	}
	return;
}

#endif