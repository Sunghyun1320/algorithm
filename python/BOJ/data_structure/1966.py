import sys
input = sys.stdin.readline


##############################################
# 리스트에서 1번 인덱스 값만 반환하는 함수(map 용)
def T_F(list_):
    return list_[1]


##############################################
t = int(input())

# 테스트 개수만큼 반복
for _ in range(t):
    n, m = map(int, input().split())

    data = list(map(int, input().split()))

    for i in range(n):
        data[i] = [i, data[i]]

    answer = 0
    while data:
        index, imp = data[0]

        if imp < max(map(T_F, data)):
            data.append(data.pop(0))
        else:
            data.pop(0)
            answer += 1
            if index == m:
                break

    print(answer)
