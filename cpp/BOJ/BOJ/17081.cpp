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

//������� R,D,L,U
const int dx[4] = { 0,1,0,-1 };
const int dy[4] = { 1,0,-1,0 };

int N, M, K, L, X, Y;
char map[100][100];
int detail[100][100];
int order_size;
int order[5000];

// �÷��̾� ����ü, �÷��̾� ����
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

// ���� ����ü 
// ���ʹ� �ִ�ü���� �� �ʿ䰡 �����Ƿ� ü�¸� ����
struct Monster {
	std::string name;
	int ATT;
	int DEF;
	int HP;
	int EXP;
} monster[10000];

// ������ ����ü
// type�� ���� �Ǵ� ���ϰ�� value�� ��ġ
// type�� �Ǽ������� ���
// 0 : ���� �¸��� ü�� 3ȸ��
// 1 : ����� ������ġ ȸ��
// 2 : ��� ���� ù ���ݽ� 2�� ����
// 3 : ����ġ ȹ�� 1.2��
// 4 : �������� 1���� �� 2�� ȿ�� 3��� ����
// 5 : ���� ������ �ִ�ü�� ȸ��, ���� ù ���� 0;
// 6 : ȿ������ �ڸ��� ����
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


// Ʈ�� ��� �Լ�
void SpikeTrep() {
	if (player.acc[4]) player.HP--;
	else player.HP -= 5;
}

// ���Ϳ� �ο�� �Լ�
void fight(Monster monster, bool isboss) {
	int my_dmg = max(1, player.ATT + player.W - monster.DEF);
	int mon_dmg = max(1, monster.ATT - player.DEF - player.A);
	int mon_HP = monster.HP;

	//�Ǽ����� ȿ�� �ߵ����� ù ���� ����
	if (player.acc[2]){
		if (player.acc[4])
			mon_HP = max(0, mon_HP - max(1, (player.ATT + player.W) * 3 - monster.DEF));
		else
			mon_HP = max(0, mon_HP - max(1, (player.ATT + player.W) * 2 - monster.DEF));
		player.HP -= mon_dmg;
	}

	// �Ǽ����� ȿ���� ���������� �ִ�ü�� ȸ�� �� ������ ����
	// ù ���� ���� �ִ�ü�� ���¶�� �ǹ�
	if (isboss && player.acc[5]) {
		player.HP = player.MAX_HP;
	}

	// ���͸� ���̱� ���� Ƚ���� -1 ����ŭ �������� �Դ´�.
	// ���� ü���� �������� ���� ��ŭ �������� ������, ������ ���� �����̸� 1�� ���� ����
	//int temp = int(monster.HP / my_dmg);
	//int check = bool(monster.HP%my_dmg) ? 0 : 1;
	int fightcount = int(mon_HP / my_dmg) - (bool(mon_HP%my_dmg) ? 0 : 1);
	player.HP -= mon_dmg * fightcount;
	
}

// ����ġ ȹ�� �Լ�
void GetEXP(int exp) {
	player.EXP += exp;

	//�Ǽ����� ȿ���� �߰� ����ġ
	if (player.acc[3])
		player.EXP += int(exp * 0.2);

	//������ ���� üũ
	if (player.EXP < player.LV * 5) return;

	player.LV += 1;
	player.EXP = 0;
	player.MAX_HP += 5;
	player.ATT += 2;
	player.DEF += 2;
	player.HP = player.MAX_HP;
}

// ��Ȱ ������ ���
void reverse() {
	// ������ �Ҹ� ��
	player.acc[1] = false;
	player.count_acc -= 1;
	// �ִ�ü�� ȸ��
	player.HP = player.MAX_HP;
	//�ʱ� ��ġ ��Ȱ
	player.X = X;
	player.Y = Y;
}

//����� ����ϴ� �Լ�
//�׸���� ��, ���ΰ����±��� ���
//������ ����� ���ο��� ���
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

		// �̵� �Ұ��� ���
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
		//��ĭ�� ���
		if (map[nx][ny] == '.') {
			player.X = nx;
			player.Y = ny;
			continue;
		}
		// ���� ���� ��
		if (map[nx][ny] == '&') {
			//�ο�
			fight(monster[detail[nx][ny]], false);
			//�й�� ��� ��� �� ����
			if (player.HP <= 0) {
				if (player.acc[1]) { reverse(); continue; }
				player.HP = 0;
				printresult(T);
				std::cout << "YOU HAVE BEEN KILLED BY " << monster[detail[nx][ny]].name << "..\n";
				return 0;
			}
			// �¸��� �̵� �� ����ġ ȹ��, ���� ����
			player.X = nx;
			player.Y = ny;

			if (player.acc[0]) player.HP = min(player.MAX_HP, player.HP + 3);

			GetEXP(monster[detail[nx][ny]].EXP);
			map[nx][ny] = '.';
			continue;
		}
		// ���� ���� �ִٸ�
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
		//������ ȹ�� ��
		if (map[nx][ny] == 'B') {
			player.X = nx;
			player.Y = ny;
			Item getitem = item[detail[nx][ny]];
			// ���� Ȥ�� ���� ��ü
			if (getitem.type == 'W') player.W = getitem.value;
			else if (getitem.type == 'A') player.A = getitem.value;
			//�Ǽ������� ���
			else if (getitem.type == 'O') {
				//4���� ä������ ȹ�� �Ұ�
				if (player.count_acc >= 4) { map[nx][ny] = '.'; continue; }
				// �̹� ȹ���� �������̸� �н�
				if (player.acc[getitem.value]) { map[nx][ny] = '.'; continue; }

				// ���� ���̸� ȹ��
				player.acc[getitem.value] = true;
				player.count_acc++;
			}

			map[nx][ny] = '.';
			continue;
		}
		//���� ���� ��
		if (map[nx][ny] == 'M') {
			//�ο�
			fight(monster[detail[nx][ny]], true);
			//�й�� ��� ��� �� ����
			if (player.HP <= 0) {
				if (player.acc[1]) { reverse(); continue; }
				player.HP = 0;
				printresult(T);
				std::cout << "YOU HAVE BEEN KILLED BY " << monster[detail[nx][ny]].name << "..\n";
				return 0;
			}
			// �¸��� �̵� �� ����ġ ȹ��, ���� ����, ��� ����� ����
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