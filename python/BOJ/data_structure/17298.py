import sys
input_ = sys.stdin.readline
#########################################
n = int(input())
input_data = list(map(int, input_().split()))

# 값 비교를 위한 최대값 출력시 -1로 바꿔서 출력
INF = 1000001

# 정답이 역순으로 저장되는 리스트
NGE = [INF]
# 역순으로 탐색, 마지막 값은 무조건 -1이므로 생략
for index in range(n-2, -1, -1):
    # 다음 값과 비교해서 다음 값이크면 바로 NGE에 추가
    if input_data[index] < input_data[index + 1]:
        NGE.append(input_data[index + 1])

    # 아니면 NGE에서 역순으로 보며 자신보다 큰 수 추가
    else:
        for i in range(len(NGE)-1, -1, -1):
            if input_data[index] < NGE[i]:
                NGE.append(NGE[i])
                break


# 역순으로 출력
for i in range(n-1, -1, -1):
    if NGE[i] == INF:
        print(-1, end = " ")
        continue

    print(NGE[i], end = " ")

