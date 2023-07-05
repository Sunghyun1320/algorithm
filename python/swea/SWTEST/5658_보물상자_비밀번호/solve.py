import sys
sys.stdin = open("input.txt")
#############################################
from collections import deque
change = {
    '0': 0,
    '1': 1,
    '2': 2,
    '3': 3,
    '4': 4,
    '5': 5,
    '6': 6,
    '7': 7,
    '8': 8,
    '9': 9,
    'A': 10,
    'B': 11,
    'C': 12,
    'D': 13,
    'E': 14,
    'F': 15,
}
#############################################

T = int(input())

for test_case in range(1, T+1):
    n, k = map(int, input().split())

    data = deque(list(input().rstrip()))

    temp = {}

    for turn in range(n//4):
        for i in range(4):
            num = 0
            for j in range(n // 4):
                s = i * (n//4)
                num += change[data[s+j]] * (16**(n//4 - j - 1))

            if temp.get(num, False):
                continue

            temp[num] = True

        data.append(data.popleft())

    arr = list(temp.keys())

    arr.sort(reverse=True)

    print(f"#{test_case} {arr[k-1]}")
