import sys
input = sys.stdin.readline
##########################################
# n은 동굴 길이, h는 동굴 깊이
# n은 짝수
n, h = map(int, input().split())

# 종유석
up = [0 for _ in range(h)]
# 석순
down = [0 for _ in range(h)]

# 석순과 종유석을 입력받아서 높이 개수 세기
for i in range(n):
    # 석순이나 종유석의 크기를 나타내는 변수
    stone = int(input())

    # 석순
    if i % 2 == 0:
        down[h-stone] += 1

    # 종유석
    else:
        up[stone-1] += 1

min_value = n+1
min_count = 0

count = n//2

for i in range(h):
    count += down[i]

    if count < min_value:
        min_value = count
        min_count = 1
    elif count == min_value:
        min_count += 1

    count -= up[i]


print(min_value, min_count)