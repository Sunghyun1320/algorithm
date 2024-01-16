#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>

int T, N, K;
int time[1001];
std::vector<int> rool[1001];
int target;
int answer[1001];
bool check[1001];

int max(int a, int b) {
	if (a > b) return a;
	return b;
}

//�ʿ��� �ð��� ��ͷ� Ž���ϴ� �Լ�
int need_time(int build) {
	//�̹� �ʿ��� �ð��� ���Ǿ��ų�, �̸� ���������ϴ� ������ �ִٸ� �� ��ȯ
	if (rool[build].size() == 0) return time[build];
	if (check[build]) return answer[build];

	// ������ ����� �ϴ� ������ ���� �����ɸ��� �� ����
	int temp = 0;
	// ������ ����� �ϴ� ������ �ʿ�ð� ��� �� �ִ밪 ����
	for (int i = 0; i < rool[build].size(); i++) {
		temp = max(temp, need_time(rool[build][i]));
	}

	// �ʿ�ð� ���� �� ��ȯ
	answer[build] = temp + time[build];
	check[build] = true;

	return answer[build];

}

int solve() {
	// ���� ���� �� �ʱ�ȭ
	for (int i = 0; i < 1001; i++) {
		check[i] = false;
		rool[i].clear();
	}

	// �� �޾ƿ���
	std::cin >> N >> K;
	for (int i = 0; i < N; i++) {
		std::cin >> time[i + 1];
	}
	// ������ a���� ������ ���������ϴ� ������ ����Ʈ�� ����
	for (int i = 0; i < K; i++) {
		int x, y;
		std::cin >> x >> y;
		rool[y].push_back(x);
	}
	// ���� ���� ����
	std::cin >> target;
	
	//�ʿ�ð� ����� ���
	std::cout << need_time(target) << "\n";

	return 0;
}

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> T;

	// T���� solve()����
	for (int t = 0; t < T; t++) {
		solve();
	}

	return 0;

}