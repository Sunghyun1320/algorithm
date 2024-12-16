import sys
input = sys.stdin.readline
#########################################
t = int(input())

for _ in range(t):
    n, m = map(int, input().split())

    input_data = [list(map(int, input().split())) for __ in range(n)]

    # 행의 합과 열의 누적합을 저장하는 리스트
    sum_h = [0 for _ in range(n)]
    sum_v = [0 for _ in range(n)]

    # 행과 열의 누적합 저장
    for i in range(n):
        for j in range(n):
            sum_h[i] += input_data[j][i]
            sum_v[i] += input_data[i][j]

    # 연산 적용
    for ___ in range(m):
        r1, c1, r2, c2, v = map(int, input().split())

        # 행에 누적합 계산
        for i in range(r1-1, r2):
            sum_v[i] += v * (c2 - c1 + 1)
        
        # 열에 누적합 계산
        for i in range(c1-1, c2):
            sum_h[i] += v * (r2 - r1 + 1)

    # 값 출력
    for i in sum_v:
        print(i, end = " ")
    print()

    for i in sum_h:
        print(i, end = " ")
    print()


