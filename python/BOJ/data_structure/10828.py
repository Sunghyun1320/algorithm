import sys
input = sys.stdin.readline
###########################################


def Push(x):
    stack.append(x)

def Pop():
    if len(stack) == 0:
        print(-1)
        return

    print(stack.pop(-1))

def Size():
    print(len(stack))

def Empty():
    if len(stack) == 0:
        print(1)
    else:
        print(0)

def Top():
    if len(stack) == 0:
        print(-1)
        return

    print(stack[-1])


###########################################
num_order = int(input())
stack = []

for _ in range(num_order):
    order = list(input().split())

    if order[0] == "push":
        Push(order[1])
    if order[0] == "pop":
        Pop()
    if order[0] == "size":
        Size()
    if order[0] == "empty":
        Empty()
    if order[0] == "top":
        Top()