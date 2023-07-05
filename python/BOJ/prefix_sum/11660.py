import sys
input = sys.stdin.readline
##########################################
n, m = map(int, input().split())

# 누적합이 저장될 배열
sum_data = [[0 for _ in range(n+1)] for _ in range(n+1)]
    
# 2차원 누적합 저장
for i in range(1, n+1):
    a = list(map(int, input().split()))
    sum_temp = 0
    for j in range(1, n+1):
        sum_temp += a[j-1]
        sum_data[i][j] = sum_data[i-1][j] + sum_temp
        
# 누적합 출력
for _ in range(m):
    x1, y1, x2, y2 = map(int, input().split())
    print(sum_data[x2][y2] - sum_data[x1 - 1][y2] - sum_data[x2][y1 - 1] + sum_data[x1 - 1][y1 - 1])


