import sys
sys.stdin = open("input.txt")
#############################################
from collections import deque

def time_check(set):
    stair_0 = []
    stair_1 = []

    # 각 사람들이 내려가는 계단에 따라 구분해서 거리를 추가해 줌
    for i in range(people_count):
        if set & (1 << i):
            stair_1.append(abs(stair[1][0] - people[i][0]) + abs(stair[1][1] - people[i][1]))

        else:
            stair_0.append(abs(stair[0][0] - people[i][0]) + abs(stair[0][1] - people[i][1]))

    # 먼저 도착하는 순서대로 처리하므로 정렬후 큐형태로 저장
    stair_0_wait = deque(sorted(stair_0))
    stair_1_wait = deque(sorted(stair_1))
    # 계단에 사람이 있는지 체크
    stair_0 = [0, 0, 0]
    stair_1 = [0, 0, 0]

    # 경과 시간
    time = 0
    # 계단을 다 내려간 사람 수
    count = 0

    global answer
    while True:
        time += 1

        # 최소 시간보다 오래걸리면 리턴
        if time >= answer:
            return

        # 각 계단에서 사람이 있으면 한칸씩 내려가고
        # 0이 되어 다 내려가면 내려간 사람 + 1
        for i in range(3):
            if stair_0[i] != 0:
                stair_0[i] -= 1
                if stair_0[i] == 0:
                    count += 1

            if stair_1[i] != 0:
                stair_1[i] -= 1
                if stair_1[i] == 0:
                    count += 1

        # 모든 사람이 다 내려갔으면 시간 최소값 갱신
        if count == people_count:
            answer = min(answer, time)
            return

        # 각 계단에 대해서
        for i in range(3):
            # 빈칸이 있고, 대기 인원이 있을 때 계단을 내려감
            # 근데 방금 도착했으면 1분 후에 내려 갈수있으므로 stair_0_wait[0] < time인 경우에만
            if stair_0[i] == 0 and stair_0_wait and stair_0_wait[0] < time:
                stair_0[i] = stair[0][2]
                stair_0_wait.popleft()

            # 계단 1에서도 비어있고 대기 인원이 있으면 내려감 마찬가지로 시간처리
            if stair_1[i] == 0 and stair_1_wait and stair_1_wait[0] < time:
                stair_1[i] = stair[1][2]
                stair_1_wait.popleft()


#############################################
T = int(input())

for test_case in range(1, T+1):
    N = int(input())

    graph = [list(map(int, input().split())) for _ in range(N)]

    people = []
    stair = []
    for i in range(N):
        for j in range(N):
            # 사람의 위치 기록
            if graph[i][j] == 1:
                people.append([i, j])

            # 계단의 위치와 길이 기록
            elif graph[i][j] != 0:
                stair.append([i, j, graph[i][j]])

    people_count = len(people)

    answer = int(1e9)
    # 각 사람들이 내려가는 계단을 선택하는 경우의 수를
    # 비트마스킹으로 표현
    for i in range(1 << people_count):
        time_check(i)

    print(f"#{test_case} {answer}")