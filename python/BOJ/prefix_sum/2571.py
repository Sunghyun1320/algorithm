import sys
input = sys.stdin.readline
##########################################################
n = int(input())

paper = [[0 for _ in range(101)] for _ in range(101)]

# 입력받은 색종이를 저장
for _ in range(n):
    a, b = map(int, input().split())

    for i in range(a, a+10):
        for j in range(b, b+10):
            paper[i][j] = 1

# 행방향, 열방향 누적합을 저장하는 2차원 배열
# 101번째 인덱스 접근을 위한 크기 102
sum_h = [[0 for _ in range(102)] for _ in range(102)]
sum_v = [[0 for _ in range(102)] for _ in range(102)]

# 행방향, 열방향으로 누적합을 구함
for i in range(1, 101):
    for j in range(1, 101):
        if paper[i][j] == 1:
            sum_v[i][j] = sum_v[i][j-1] + 1
            sum_h[i][j] = sum_h[i-1][j] + 1


##########################################################
answer = 0
for i in range(1, 101):
    for j in range(1, 101):
        #####################################################
        # # 0이아닌 (높이를 가지고 있고) 그 다음 칸이 0이어서 최대 높이 일 때
        # if sum_v[i][j] != 0 and sum_v[i][j+1] == 0:
        #     # 그 높이 기준으로 행으로 움직이며
        #     # 같은 높이인 칸의 넓이를 구함
        #     for k in range(i, 101):
        #         if sum_v[k][j] != sum_v[k+1][j]:
        #             answer = max(answer, sum_v[i][j] * (k - i + 1))
        #             break
        #
        # # 0이아닌 (높이를 가지고 있고) 그 다음 칸이 0이어서 최대 높이 일 때
        # if sum_h[j][i] != 0 and sum_h[j+1][i] == 0:
        #     # 그 높이를 기준으로 열을 움직이며
        #     # 같은 높이인 칸의 넓이를 구함
        #     for k in range(i, 101):
        #         if sum_h[j][k] != sum_h[j][k+1]:
        #             answer = max(answer, sum_h[j][i] * (k - i + 1))
        #             break
        #####################################################
        if paper[i][j] == 0:
            continue

        h = 100
        for k in range(j, 100):
            h = min(h, sum_h[i][k])

            if h == 0:
                break

            answer = max(answer, h*(k-j+1))


print(answer)
