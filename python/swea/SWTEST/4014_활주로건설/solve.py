import sys
sys.stdin = open("input.txt")
#############################################
def check(arr):
    short_arr = []
    num = arr[0]
    count = 0
    for i in range(N):
        # 경사 높이 차가 2 이상이면 활주로 불가
        if abs(num - arr[i]) >= 2:
            return False

        # 각 높이의 길이를 저장하려함
        if num == arr[i]:
            count += 1

        # 경사로가 낮아지면 True
        elif num > arr[i]:
            short_arr.append([count, True])
            count = 1
            num = arr[i]

        # 경사로가 높아지면 False
        elif num < arr[i]:
            short_arr.append([count, False])
            count = 1
            num = arr[i]

    # 마지막 높이의 개수 추가
    short_arr.append([count, None])

    for i in range(len(short_arr) - 1):
        if short_arr[i][1]:
            short_arr[i+1][0] -= X
            if short_arr[i+1][0] < 0:
                return False

        else:
            short_arr[i][0] -= X
            if short_arr[i][0] < 0:
                return False

    return True


#############################################
T = int(input())

for test_case in range(1, T+1):
    N, X = map(int, input().split())

    graph = [list(map(int, input().split())) for _ in range(N)]

    answer = 0
    for i in graph:
        if check(i):
            answer += 1

    new_graph = [[0 for _ in range(N)] for _ in range(N)]
    for i in range(N):
        for j in range(N):
            new_graph[i][j] = graph[j][i]

    for i in new_graph:
        if check(i):
            answer += 1

    print(f"#{test_case} {answer}")
