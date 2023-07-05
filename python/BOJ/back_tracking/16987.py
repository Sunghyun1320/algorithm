import sys
input = sys.stdin.readline
######################################
def attack_agg(n, count = 0, depth = 0):
    global answer
    # 이미 정답이 최대개수이면 더 연산 안하고 리턴
    if answer == n:
        return

    # 최대깊이가 되거나 깨진 계란이 n-1인경우 최대값 갱신
    if depth == n or count == n - 1:
        answer = max(answer, count)
        return

    # 이번 달걀이 이미 깨진 달걀이면 다음 계란 들기
    if egg[depth][2]:
        attack_agg(n, count, depth+1)
        return

    # 모든 계란에 대해서
    for i in range(n):
        # 자기자신은 제외
        if i == depth:
            continue

        # 이미 깨진 계란이면 제외
        if egg[i][2]:
            continue

        # 현재까지 깨진 달걀
        count_local = count

        # 각각의 내구도에서 서로의 무게만큼 빼주기
        egg[i][0] -= egg[depth][1]
        egg[depth][0] -= egg[i][1]

        # 0이하가 되면 깨짐 처리후 깨진 달걀수 추가
        if egg[i][0] <= 0:
            egg[i][2] = True
            count_local += 1

        if egg[depth][0] <= 0:
            egg[depth][2] = True
            count_local += 1

        # 다음 달걀 들러 가기
        attack_agg(n, count_local, depth+1)

        # 계란 원상 복구
        egg[i][0] += egg[depth][1]
        egg[depth][0] += egg[i][1]
        egg[i][2] = False
        egg[depth][2] = False


######################################
n = int(input())

egg = []

for _ in range(n):
    a, b = map(int, input().split())
    egg.append([a, b, False])


answer = 0
attack_agg(n)

print(answer)