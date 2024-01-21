#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

int min(int a, int b){
	if (a < b) return a;
	return b;
}

int max(int a, int b) {
	if (a < b) return b;
	return a;
}

//순서대로 R,D,L,U
const int dx[4] = { 0,1,0,-1 };
const int dy[4] = { 1,0,-1,0 };

int N, M, K, L, X, Y;
char map[100][100];
int detail[100][100];
int order_size;
int order[5000];

// 플레이어 구조체, 플레이어 선언
struct Player {
	int X, Y;
	int LV = 1;
	int MAX_HP = 20;
	int HP = 20;
	int ATT = 2;
	int DEF = 2;
	int EXP = 0;
	int W = 0;
	int A = 0;
	bool acc[7] = { false };
	int count_acc = 0;
} player;

// 몬스터 구조체 
// 몬스터는 최대체력을 알 필요가 없으므로 체력만 저장
struct Monster {
	std::string name;
	int ATT;
	int DEF;
	int HP;
	int EXP;
} monster[10000];

// 아이템 구조체
// type가 무기 또는 방어구일경우 value는 수치
// type가 악세서리일 경우
// 0 : 전투 승리시 체력 3회복
// 1 : 사망시 시작위치 회귀
// 2 : 모든 전투 첫 공격시 2배 공격
// 3 : 경험치 획득 1.2배
// 4 : 가시피해 1고정 및 2번 효과 3배로 변경
// 5 : 보스 전투시 최대체력 회복, 보스 첫 피해 0;
// 6 : 효과없음 자리만 차지
struct Item {
	char type;
	int value;
} item[10000];


void GetInfo() {
	char temp;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			std::cin >> temp;
			if (temp == '.') {}
			else if (temp == '#') {}
			else if (temp == 'B') { L++; }
			else if (temp == '^') {}
			else if (temp == '&') { K++; }
			else if (temp == 'M') { K++; }
			else if (temp == '@') { player.X = i; player.Y = j; X = i; Y = j; temp = '.'; }

			map[i][j] = temp;
		}
	}
}

int ChangeACCNum() {
	char type[2];
	std::cin >> type[0] >> type[1];
	if (type[0] == 'H' && type[1] == 'R') return 0;
	if (type[0] == 'R' && type[1] == 'E') return 1;
	if (type[0] == 'C' && type[1] == 'O') return 2;
	if (type[0] == 'E' && type[1] == 'X') return 3;
	if (type[0] == 'D' && type[1] == 'X') return 4;
	if (type[0] == 'H' && type[1] == 'U') return 5;
	if (type[0] == 'C' && type[1] == 'U') return 6;

	return 0;
}

void GetDetailInfo() {
	int x, y;
	for (int i = 0; i < K; i++) {
		std::cin >> x >> y;
		x--;
		y--;
		detail[x][y] = i;
		std::cin >> monster[i].name >> monster[i].ATT >> monster[i].DEF >> monster[i].HP >> monster[i].EXP;
	}

	for (int i = 0; i < L; i++) {
		std::cin >> x >> y;
		x--;
		y--;
		detail[x][y] = i;
		std::cin >> item[i].type;
		if (item[i].type == 'O') {
			item[i].value = ChangeACCNum();
		}
		else std::cin >> item[i].value;
	}
}

void GetOrder() {
	std::string order_str;
	std::cin >> order_str;
	order_size = order_str.size();
	for (int i = 0; i < order_size; i++) {
		if (order_str[i] == 'R') order[i] = 0;
		else if (order_str[i] == 'D') order[i] = 1;
		else if (order_str[i] == 'L') order[i] = 2;
		else if (order_str[i] == 'U') order[i] = 3;
	}
}


// 트랩 밟는 함수
void SpikeTrep() {
	if (player.acc[4]) player.HP--;
	else player.HP -= 5;
}

// 몬스터와 싸우는 함수
void fight(Monster monster, bool isboss) {
	int my_dmg = max(1, player.ATT + player.W - monster.DEF);
	int mon_dmg = max(1, monster.ATT - player.DEF - player.A);
	int mon_HP = monster.HP;

	//악세서리 효과 발동으로 첫 전투 진행
	if (player.acc[2]){
		if (player.acc[4])
			mon_HP = max(0, mon_HP - max(1, (player.ATT + player.W) * 3 - monster.DEF));
		else
			mon_HP = max(0, mon_HP - max(1, (player.ATT + player.W) * 2 - monster.DEF));
		player.HP -= mon_dmg;
	}

	// 악세서리 효과로 보스전투시 최대체력 회복 및 데미지 무시
	// 첫 전투 이후 최대체력 상태라는 의미
	if (isboss && player.acc[5]) {
		player.HP = player.MAX_HP;
	}

	// 몬스터를 죽이기 위한 횟수의 -1 번만큼 데미지를 입는다.
	// 몬스터 체력을 데미지로 나눈 몫만큼 데미지를 입지만, 나머지 없이 딱딜이면 1대 적게 맞음
	//int temp = int(monster.HP / my_dmg);
	//int check = bool(monster.HP%my_dmg) ? 0 : 1;
	int fightcount = int(mon_HP / my_dmg) - (bool(mon_HP%my_dmg) ? 0 : 1);
	player.HP -= mon_dmg * fightcount;
	
}

// 경험치 획득 함수
void GetEXP(int exp) {
	player.EXP += exp;

	//악세서리 효과로 추가 경험치
	if (player.acc[3])
		player.EXP += int(exp * 0.2);

	//레벨업 여부 체크
	if (player.EXP < player.LV * 5) return;

	player.LV += 1;
	player.EXP = 0;
	player.MAX_HP += 5;
	player.ATT += 2;
	player.DEF += 2;
	player.HP = player.MAX_HP;
}

// 부활 아이템 사용
void reverse() {
	// 아이템 소멸 후
	player.acc[1] = false;
	player.count_acc -= 1;
	// 최대체력 회복
	player.HP = player.MAX_HP;
	//초기 위치 부활
	player.X = X;
	player.Y = Y;
}

//결과를 출력하는 함수
//그리드와 턴, 주인공상태까지 출력
//게임의 결과는 메인에서 출력
void printresult(int T) {
	if(player.HP > 0) map[player.X][player.Y] = '@';
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			std::cout << map[i][j];
		}
		std::cout << "\n";
	}

	std::cout << "Passed Turns : " << T+1 << '\n';
	std::cout << "LV : " << player.LV << '\n';
	std::cout << "HP : " << player.HP << '/' << player.MAX_HP << '\n';
	std::cout << "ATT : " << player.ATT << '+' << player.W << '\n';
	std::cout << "DEF : " << player.DEF << '+' << player.A << '\n';
	std::cout << "EXP : " << player.EXP << '/' << player.LV * 5 << '\n';

}

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> N >> M;

	GetInfo();
	GetOrder();
	GetDetailInfo();

	for (int T = 0; T < order_size; T++)
	{
		if (player.HP > player.MAX_HP)
			int a = 0;
		int nx = player.X + dx[order[T]];
		int ny = player.Y + dy[order[T]];

		// 이동 불가의 경우
		if (nx < 0 || nx >= N || ny < 0 || ny >= M || map[nx][ny] == '#') {
			if (map[player.X][player.Y] == '^') {
				SpikeTrep();
				if (player.HP <= 0) {
					if (player.acc[1]) { reverse(); continue; }
					player.HP = 0;
					printresult(T);
					std::cout << "YOU HAVE BEEN KILLED BY SPIKE TRAP..\n ";
					return 0;
				}
			};
			continue;
		}
		//빈칸인 경우
		if (map[nx][ny] == '.') {
			player.X = nx;
			player.Y = ny;
			continue;
		}
		// 몬스터 조우 시
		if (map[nx][ny] == '&') {
			//싸움
			fight(monster[detail[nx][ny]], false);
			//패배시 결과 출력 후 종료
			if (player.HP <= 0) {
				if (player.acc[1]) { reverse(); continue; }
				player.HP = 0;
				printresult(T);
				std::cout << "YOU HAVE BEEN KILLED BY " << monster[detail[nx][ny]].name << "..\n";
				return 0;
			}
			// 승리시 이동 후 경험치 획득, 몬스터 삭제
			player.X = nx;
			player.Y = ny;

			if (player.acc[0]) player.HP = min(player.MAX_HP, player.HP + 3);

			GetEXP(monster[detail[nx][ny]].EXP);
			map[nx][ny] = '.';
			continue;
		}
		// 가시 위에 있다면
		if (map[nx][ny] == '^') { 
			player.X = nx;
			player.Y = ny;
			SpikeTrep(); 
			if (player.HP <= 0) {
				if (player.acc[1]) { reverse(); continue; }
				player.HP = 0;
				printresult(T);
				std::cout << "YOU HAVE BEEN KILLED BY SPIKE TRAP..\n ";
				return 0;
			}
		}
		//아이템 획득 시
		if (map[nx][ny] == 'B') {
			player.X = nx;
			player.Y = ny;
			Item getitem = item[detail[nx][ny]];
			// 무기 혹은 방어구시 교체
			if (getitem.type == 'W') player.W = getitem.value;
			else if (getitem.type == 'A') player.A = getitem.value;
			//악세서리일 경우
			else if (getitem.type == 'O') {
				//4개를 채웠으면 획득 불가
				if (player.count_acc >= 4) { map[nx][ny] = '.'; continue; }
				// 이미 획득한 아이템이면 패스
				if (player.acc[getitem.value]) { map[nx][ny] = '.'; continue; }

				// 없는 템이면 획득
				player.acc[getitem.value] = true;
				player.count_acc++;
			}

			map[nx][ny] = '.';
			continue;
		}
		//보스 조우 시
		if (map[nx][ny] == 'M') {
			//싸움
			fight(monster[detail[nx][ny]], true);
			//패배시 결과 출력 후 종료
			if (player.HP <= 0) {
				if (player.acc[1]) { reverse(); continue; }
				player.HP = 0;
				printresult(T);
				std::cout << "YOU HAVE BEEN KILLED BY " << monster[detail[nx][ny]].name << "..\n";
				return 0;
			}
			// 승리시 이동 후 경험치 획득, 몬스터 삭제, 결과 출력후 리턴
			player.X = nx;
			player.Y = ny;
			if (player.acc[0]) player.HP = min(player.MAX_HP, player.HP + 3);

			GetEXP(monster[detail[nx][ny]].EXP);
			map[nx][ny] = '.';
			printresult(T);
			std::cout << "YOU WIN!\n";
			return 0;
		}

	}
	printresult(order_size - 1);
	std::cout << "Press any key to continue.\n";

	return 0;
}