import sys
import heapq
input = sys.stdin.readline
####################################################
n, k = map(int, input().split())

jam = []

for _ in range(n):
    heapq.heappush(jam, list(map(int, input().split())))

bag = []
for _ in range(k):
    bag.append(int(input()))

bag.sort()
####################################################
result = 0

can_input_jam = []
for max_m in bag:
    for _ in jam:
        if jam[0][0] > max_m:
            break
        heapq.heappush(can_input_jam, -heapq.heappop(jam)[1])

    if can_input_jam:
        result -= heapq.heappop(can_input_jam)

    elif not jam:
        break

print(result)
