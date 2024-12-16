import sys
input = sys.stdin.readline
###################################################

c, r = map(int, input().split())
n = 0
order = []

x = y = 0


while True:
    n += 1
    dx, dy = map(int, input().split())
    if dx == 0 and dy == 0:
        break

    order.append((dx, dy,))

for dx, dy in order:
    nx = x + dx
    ny = y + dy

    if nx > c:
        nx = c

    elif nx < 0:
        nx = 0

    if ny > r:
        ny = r

    elif ny < 0:
        ny = 0

    x, y = nx, ny

    print(x, y)





