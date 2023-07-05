import sys
input = sys.stdin.readline
################################################
n = int(input())

input_data = list(map(int, input().split()))

answer = [-1] * n

# 2번째 기둥부터 체크
for i in range(1, n):
    index = i - 1
    while True:
        # 지금 체크하는 기둥이 나보다 크면 저장 후 멈춤
        if input_data[index] > input_data[i]:
            answer[i] = index
            break

        # 작으면
        else:
            # 해당 기둥이 수신된 기둥 체크
            # 만약 없으면 0 입력후 멈춤
            if answer[index] == -1:
                answer[i] = -1
                break

            # 그 작은 기둥이 인식된 기둥과 비교
            index = int(answer[index])


for num in answer:
    print(num+1, end = " ")
