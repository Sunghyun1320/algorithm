import sys
input = sys.stdin.readline
########################################
def n_queen(n, status, depth = 0):
    # 현재 열에서 선택할 수 있는 행을 저장하는 리스트
    this_status = status.copy()

    # 최대깊이 도달시 개수 +1
    if depth == n:
        global count
        count += 1

    # 현재까지 선택된 status에 따라서 대각선 처리 해주기
    for i in range(n):
        if status[i] < 0:
            continue

        # 대각선은 선택된 열과 이번 열의 차이 만큼 i에서 더하고 빼진 값
        # 그리고 그 대각선이 이미 선택된 행이면 어차피 못고르는 행이므로 처리 안함
        if 0 <= i + (depth - status[i]) < n and this_status[i + depth - status[i]] == -1:
            this_status[i + depth - status[i]] = -2

        if 0 <= i - (depth - status[i]) < n and this_status[i - depth + status[i]] == -1:
            this_status[i - depth + status[i]] = -2

    # 선택가능한 행을 선택해서
    # 현재 깊이에서 선택함을 저장하고 다음 깊이로 넘어가기
    # 없으면 알아서 돌아감(백 트래킹)
    for i in range(n):
        if this_status[i] == -1:
            status[i] = depth
            n_queen(n, status, depth+1)
            status[i] = -1


########################################
n = int(input())
# 정답이 저장될 개수
count = 0
# 각 행이 어느 열에서 선택되었는지 저장될 리스트
status = [-1 for _ in range(n)]

# 연산 시작
n_queen(n, status)

# 출력
print(count)

