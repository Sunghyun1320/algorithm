import sys
input = sys.stdin.readline
################################################
# 윷놀이 판
main_line = [i*2 for i in range(21)]
order_line_1 = [10, 13, 16, 19, 25]
order_line_2 = [20, 22, 24, 25]
order_line_3 = [30, 28, 27, 26, 25]
order_line_4 = [25, 30, 35, 40]
goal = [40]

line = [main_line, order_line_1, order_line_2, order_line_3, order_line_4, goal]

# dfs로 탐색
def dfs(point = 0, depth = 0):
    # 최대깊이에서 최대값 갱신 후 리턴
    if depth == 10:
        global answer
        answer = max(answer, point)
        return

    # 이번 주사위
    order = dice[depth]

    # 4개의 말에 대해서
    for horse_num in range(4):
        # 이미 도착한 말이면 다음 말 선택
        if horse[horse_num][2]:
            continue

        # 위치 복구용 저장
        now_position = [horse[horse_num][0], horse[horse_num][1]]

        # 말을 이동
        horse[horse_num][1] += order

        # 이동 후 위치가 분기점이면 라인 바꾸기
        if horse[horse_num][0] == 0 and horse[horse_num][1] == 5:
            horse[horse_num][0] = 1
            horse[horse_num][1] = 0

        elif horse[horse_num][0] == 0 and horse[horse_num][1] == 10:
            horse[horse_num][0] = 2
            horse[horse_num][1] = 0

        elif horse[horse_num][0] == 0 and horse[horse_num][1] == 15:
            horse[horse_num][0] = 3
            horse[horse_num][1] = 0

        elif horse[horse_num][0] == 0 and horse[horse_num][1] == 20:
            horse[horse_num][0] = 5
            horse[horse_num][1] = 0

        # 도착하면 좌표 바꾸고 도착 처리
        elif horse[horse_num][0] == 0 and horse[horse_num][1] > 20:
            horse[horse_num][0] = -1
            horse[horse_num][0] = -1
            horse[horse_num][2] = True

        # 분기점에 있던 말이 현재 범위를 초과하면
        elif horse[horse_num][0] != 0 and horse[horse_num][0] != 4 and horse[horse_num][0] != 5:
            # 25~40번 라인으로 이동 후 기존 라인 길이만큼 빼기
            if horse[horse_num][1] >= len(line[horse[horse_num][0]]):
                horse[horse_num][1] -= (len(line[horse[horse_num][0]]) - 1)
                horse[horse_num][0] = 4

        # 40번 위치에 도착시 40번 위치 라인으로 이동
        if horse[horse_num][0] == 4 and horse[horse_num][1] == 3:
            horse[horse_num][0] = 5
            horse[horse_num][1] = 0

        # 25~40번 라인에서 도착시 도착처리
        elif horse[horse_num][0] == 4 and horse[horse_num][1] > 3:
            horse[horse_num][0] = -1
            horse[horse_num][1] = -1
            horse[horse_num][2] = True

        # 40번 위치에서 범위 이탈시 도착 처리
        if horse[horse_num][0] == 5 and horse[horse_num][1] > 0:
            horse[horse_num][0] = -1
            horse[horse_num][1] = -1
            horse[horse_num][2] = True

        # 같은 위치에 말이 있는지 체크
        check = False

        # 4개의 말에 대해서
        for i in range(4):
            # 자기 자신이나, 도착한 말이면 패스
            if horse[i][2] or i == horse_num:
                continue

            # 같은위치의 말이 있으면 True
            if horse[i][0] == horse[horse_num][0] and horse[i][1] == horse[horse_num][1]:
                check = True

        # 같은 위치에 말이 있으면 위치 복구후 다른말 옮기기
        if check:
            horse[horse_num][0] = now_position[0]
            horse[horse_num][1] = now_position[1]
            horse[horse_num][2] = False
            continue

        # 이번 이동으로 도착하면 점수 추가 없이 다음 주사위
        if horse[horse_num][2]:
            dfs(point, depth + 1)
        # 도착이 아니면, 이번칸의 점수 추가해서 다음 주사위
        else:
            dfs(point + line[horse[horse_num][0]][horse[horse_num][1]], depth + 1)

        # 말의 원래위치로 복구
        horse[horse_num][0] = now_position[0]
        horse[horse_num][1] = now_position[1]
        horse[horse_num][2] = False


dice = list(map(int, input().split()))

horse = [[0, 0, False], [0, 0, False], [0, 0, False], [0, 0, False]]
answer = 0
dfs()

print(answer)

