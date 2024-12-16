import sys
input = sys.stdin.readline
#########################################
# 입력받은 종이에서 9개로 나눠서 종이인지 판단하는 함수
def check_paper(size, start):
    global answer

    # 체크를 시작하는 위치
    x, y = start

    paper_count = [0 for _ in range(3)]

    # 미리 9칸으로 나눠서 종이가 되는지 체크
    for i in range(3):
        for j in range(3):
            # 9칸으로 나눴을 때 시작지점
            nx = x + i * size
            ny = y + j * size
            # 현재 종이의 숫자
            paper_num = paper[nx][ny]

            # 이번 구간이 하나의 종이인지 체크하는 변수
            check = False

            # 이번 구간의 종이들 체크
            for k in range(size):
                for l in range(size):
                    # 숫자가 다른 종이가 있으면
                    if paper_num != paper[nx + k][ny + l]:
                        # 해당 구간 넘겨주기
                        check_paper(size // 3, [nx, ny])

                        # 이번구간은 종이가 아님
                        check = True
                        break
                # 종이가 아니면 멈춤
                if check:
                    break
            # 종이이면 현재 번호 +1
            else:
                paper_count[paper_num] += 1

    # 만약 9개의 구간이 하나의 종이이면
    # 그 숫자 개수 +1 하고 리턴
    for i in range(-1, 2):
        if paper_count[i] == 9:
            answer[i] += 1
            return

    # 아니면 각각 +1 하고 리턴
    for i in range(3):
        answer[i] += paper_count[i]


#########################################

n = int(input())

paper = [list(map(int, input().split())) for _ in range(n)]

answer = [0 for _ in range(3)]


check_paper(n//3, [0, 0])

print(answer[-1])
print(answer[0])
print(answer[1])

