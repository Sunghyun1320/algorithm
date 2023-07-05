import sys
sys.stdin = open("input.txt")
#############################################
from collections import deque
#############################################
T = int(input())

for test_case in range(1, T+1):
    n = int(input())

    magnetic = [deque(list(map(int, input().split()))) for _ in range(4)]

    for _ in range(n):
        check_turn = [0 for _ in range(4)]
        a, dir = map(int, input().split())
        a -= 1
        check_turn[a] = dir

        for i in range(a, 3):
            if magnetic[i][2] != magnetic[i+1][6]:
                check_turn[i+1] = -check_turn[i]

        for i in range(a, 0, -1):
            if magnetic[i][6] != magnetic[i-1][2]:
                check_turn[i-1] = -check_turn[i]

        for i in range(4):
            if check_turn[i] == 1:
                magnetic[i].appendleft(magnetic[i].pop())

            elif check_turn[i] == -1:
                magnetic[i].append(magnetic[i].popleft())

    answer = 0
    answer += magnetic[0][0]
    answer += magnetic[1][0] * 2
    answer += magnetic[2][0] * 4
    answer += magnetic[3][0] * 8

    print(f"#{test_case} {answer}")






