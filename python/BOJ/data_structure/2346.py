import sys
from collections import deque
input = sys.stdin.readline
############################################################
n = int(input())

ballon = list(map(int, input().split()))

for i in range(n):
    ballon[i] = [ballon[i], i+1]

############################################################
# deque 사용
ballon = deque(ballon)

for _ in range(n):
    #이번에 터진 풍선의 숫자와 풍선의 숫자
    order, num = ballon.popleft()
    print(num)
    #풍선이 모두 터졌으면 스톱
    if len(ballon) == 0:
        break

    #숫자에 따라 회전 방향이 달라짐
    if order > 0:
        #회전 횟수 -1 만큼 회전
        for __ in range(order - 1):
            ballon.append(ballon.popleft())
    #음수 방향일 경우
    else:
        #회전 횟수만큼 회전
        for __ in range(-order):
            ballon.appendleft(ballon.pop())
############################################################
# #자료구조 이용
# for _ in range(n):
#     #이번에 터진 풍선의 숫자와 풍선의 숫자
#     order, num = ballon.pop(0)
#     print(num)
#     #풍선이 모두 터졌으면 스톱
#     if len(ballon) == 0:
#         break
#
#     #숫자에 따라 회전 방향이 달라짐
#     if order > 0:
#         #회전 횟수 -1 만큼 회전
#         for __ in range(order - 1):
#             ballon.append(ballon.pop(0))
#     #음수 방향일 경우
#     else:
#         #회전 횟수만큼 회전
#         for __ in range(-order):
#             ballon.insert(0, ballon.pop(-1))

############################################################
# # 인덱스만 변화하며 해결
# index = 0
# # 풍선이 안남을 때 까지 반복
# while ballon:
#     #이번에 터진 풍선의 숫자와 풍선의 숫자
#     order, num = ballon.pop(index)
#     # 풍선이 남아있고, 음수 회전일 때
#     if ballon and order < 0:
#         index = (index + order) % len(ballon)
#     # 풍선이 남아있고, 양수 회전일 때
#     elif ballon:
#         index = (index + order -1) % len(ballon)
#     print(num)




