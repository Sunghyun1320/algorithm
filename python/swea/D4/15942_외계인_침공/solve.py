import sys
sys.stdin = open("input.txt")
#############################################
def find(a):
    if visited[a] != a:
        visited[a] = find(visited[a])

    return visited[a]


#############################################
T = int(input())

for test_case in range(1, T + 1):
    n, k = map(int, input().split())

    plant = list(map(int, input().split()))

    plant.sort()

    if plant[0] > k:
        print(f"#{test_case} {-1}")
        continue

    need_boat = sum(plant)

    if need_boat <= k:
        print(f"#{test_case} {0}")
        continue

    plant.append(int(1e15))

    count = 0
    visited = [i for i in range(n)]

    i = 0

    while True:
        if plant[i] <= k:
            i += 1
            continue

        attack = find(i - 1)
        visited[attack] = visited[attack - 1]
        k += plant[attack]
        need_boat -= plant[attack]
        count += 1

        if need_boat <= k:
            break

        if count == i and plant[i] > k:
            count = -1
            break

    print(f"#{test_case} {count}")





        

