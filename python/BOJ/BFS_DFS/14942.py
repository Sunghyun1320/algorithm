import sys
input = sys.stdin.readline
###############################################
n = int(input())

ant_energy = [0]
room = [[i] for i in range(n+1)]
ant_position = [i for i in range(n+1)]

for _ in range(n):
    ant_energy.append(int(input()))


tunnel = [[] for _ in range(n+1)]

for _ in range(n-1):
    a, b, length = map(int, input().split())

    tunnel[a].append((b, length,))
    tunnel[b].append((a, length,))

# print(tunnel)

visit = [1]
visited = [False for _ in range(n+1)]
cost_stack = []

go_next_ant = []

while visit:
    now_room = visit.pop()

    # 음수가 저장되어 있다면 자식노드를 모두 탐색하고 돌아온것
    comeback_check = False
    if now_room < 0:
        comeback_check = True
        now_room = -now_room

    if now_room == 1 and visited[1]:
        while go_next_ant:
            room[now_room].append(go_next_ant[-1])
            ant_position[go_next_ant.pop()] = now_room
        continue


    # 이전에 방문했다면
    if visited[now_room]:
        # 이번 방으로 넘어오는 개미들은 전부 추가하고 개미들 옮기기
        while go_next_ant:
            room[now_room].append(go_next_ant[-1])
            ant_position[go_next_ant.pop()] = now_room

        # 자식노드를 모두 돌고 왔다면
        if comeback_check:
            # 이번방에서 부모방으로 가는데 필요한 비용
            cost = cost_stack.pop()

            # 지금 방에 있는 모든 개미들에 대해서
            for i in room[now_room]:
                # 다음방으로 넘어가기 위한 비용 빼기
                ant_energy[i] -= cost
                # 넘어가도 에너지가 남아있으면 다음방 가는 리스트에 추가가
                if ant_energy[i] >= 0:
                    go_next_ant.append(i)

        continue

    visited[now_room] = True

    # 자식노드 모두 탐색 후 자신에게 돌아오기 위한 추가
    visit.append(-now_room)

    for room_, cost in tunnel[now_room]:
        if visited[room_]:
            continue

        visit.append(room_)
        visit.append(now_room)
        cost_stack.append(cost)

    # visit.pop()


for i in range(1, n+1):
    print(ant_position[i])