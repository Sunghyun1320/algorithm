import sys
sys.stdin = open("input.txt")
#############################################
def max_cost(arr, save_arr, depth = 0, cost = 0, mess = 0):
    if mess > C:
        return

    if depth == M:
        save_arr[0] = max(save_arr[0], cost)
        return

    max_cost(arr, save_arr, depth+1, cost + arr[depth] ** 2, mess + arr[depth])
    max_cost(arr, save_arr, depth+1, cost, mess)


#############################################
T = int(input())

for test_case in range(1, T+1):
    N, M, C = map(int, input().split())

    graph = [list(map(int, input().split())) for _ in range(N)]

    answer = -1
    for i in range(N):
        for j in range(N - M + 1):
            honey_a = graph[i][j:j+M]
            honey_a_cost = [0]
            max_cost(honey_a, honey_a_cost)

            for k in range(j+M, N-M+1):
                honey_b = graph[i][k:k+M]
                honey_b_cost = [0]
                max_cost(honey_b, honey_b_cost)
                answer = max(answer, honey_b_cost[0] + honey_a_cost[0])

            for k in range(i+1, N):
                for l in range(N - M + 1):
                    honey_b = graph[k][l:l+M]
                    honey_b_cost = [0]
                    max_cost(honey_b, honey_b_cost)
                    answer = max(answer, honey_b_cost[0] + honey_a_cost[0])

    print(f"#{test_case} {answer}")



