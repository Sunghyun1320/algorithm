import sys
input = sys.stdin.readline
######################################
n = int(input())

distance = [list(map(int, input().split())) for _ in range(n)]

answer = 0
# i에서 j로 가는 경로에 대해서
for i in range(n):
    for j in range(n):
        if i == j:
            continue
        # k를 거치는 경우를 따진다.
        for k in range(n):
            # 예외처리
            if k == i or k == j:
                continue

            # 만약 k를 거치는게 더 빠른 경우 불가능 케이스
            # -1 출력후 종료
            if distance[i][j] > distance[i][k] + distance[k][j]:
                print(-1)
                exit()

            # 같은 경로가 있다면 i~j경로는 필요없이 k를 거쳐가면 된다.
            if distance[i][j] == distance[i][k] + distance[k][j]:
                break

        # 다른 모든 경로가 지금 최단거리보다 멀다면 존재하는 도로
        # 정답에 거리 추가
        else:
            answer += distance[i][j]

# i -> j와 j -> i 2가지 경우가 모두 더해졌으므로 /2
print(answer//2)

