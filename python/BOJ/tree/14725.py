import sys
from copy import deepcopy
input = sys.stdin.readline
########################################
class room():
    def __init__(self, name, depth):
        self.name = name
        self.child = {}
        self.depth = depth

    # 디버깅용 이름 출력
    def __repr__(self):
        return self.name

    def add_child(self, child_room):
        # 자식은 딕셔너리 형태, 이름을 key로 인스턴스를 값으로
        self.child[child_room.name] = child_room

    # 필요없음
    # def isroop(self):
    #     return True if self.parent == -1 else False
    #
    # def isleap(self):
    #     return True if len(self.child.keys()) == 0 else False


########################################
n = int(input())

data = [list(input().split()) for _ in range(n)]
data.sort(key=lambda x: x[1:])

# 입구
enter = room("enter", -1)

for i in range(n):
    length, *path = data[i]
    length = int(length)

    # 최초의 부모는 입구
    parent = enter

    for j in range(length):
        # 지금 객체가 없으면 자식객체를 추가해준다
        if not parent.child.get(path[j], False):
            new_room = room(path[j], j)
            parent.add_child(deepcopy(new_room))

        # 다음 자식의 부모는 지금 객체가 된다.
        parent = parent.child[path[j]]

# dfs로 전위탐색하며 이름과 깊이에 맞춰 출력해준다.
visit = [enter]

while visit:
    now = visit.pop()

    if now.name != "enter":
        print("--"*now.depth, now.name, sep="")

    for next_room in list(now.child.keys())[::-1]:
        visit.append(now.child[next_room])

