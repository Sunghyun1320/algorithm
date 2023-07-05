import sys
input = sys.stdin.readline
#####################################################
n = int(input())

unit_tree = [list(map(int, input().split()))]


# 입력받은 데이터를 트리형태로 저장하기
a = n//2
while True:
    if a == 0:
        break

    new_unit = [0 for _ in range(a+1)]
    for i in range(len(unit_tree[-1])):
        new_unit[i//2] += unit_tree[-1][i]

    unit_tree.append(new_unit.copy())

    a //= 2


########################################################
m = int(input())

for _ in range(m):
    order, *detail = map(int, input().split())

    if order == 1:
        detail[0] -= 1
        i = 0
        while True:
            if i == len(unit_tree):
                break
            unit_tree[i][detail[0]] += detail[1]
            detail[0] = (detail[0]) // 2
            i += 1

        continue


    # 여기서 부턴 출력만 해보자

    i = len(unit_tree) - 1
    j = 0

    while True:
        if i == -1:
            print(j//2+1)
            break

        if unit_tree[i][j] >= detail[0]:
            i -= 1
            j *= 2
            continue

        if unit_tree[i][j] < detail[0]:
            detail[0] -= unit_tree[i][j]
            j += 1










