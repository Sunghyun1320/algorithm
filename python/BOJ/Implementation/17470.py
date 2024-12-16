from copy import deepcopy
import sys
input = sys.stdin.readline
##########################################
def cal_1():
    if result[2] % 2:
        result[1] = not result[1]

    else:
        result[0] = not result[0]

    global sample_list

    sample_list[0], sample_list[1] = sample_list[1], sample_list[0]


##########################################
def cal_2():
    if result[2] % 2:
        result[0] = not result[0]
    else:
        result[1] = not result[1]

    sample_list[0][1], sample_list[0][0] = sample_list[0][0], sample_list[0][1]
    sample_list[1][1], sample_list[1][0] = sample_list[1][0], sample_list[1][1]


##########################################
def cal_3():
    result[2] = (result[2] + 1) % 4
    cal_5()


##########################################
def cal_4():
    result[2] = (result[2] - 1) % 4
    cal_6()


##########################################
def cal_5():
    global sample_list

    new_sample = [[0, 0], [0, 0]]

    new_sample[0][0] = sample_list[1][0]
    new_sample[0][1] = sample_list[0][0]
    new_sample[1][0] = sample_list[1][1]
    new_sample[1][1] = sample_list[0][1]

    sample_list = new_sample.copy()


##########################################
def cal_6():
    global sample_list

    new_sample = [[0, 0], [0,  0]]

    new_sample[0][0] = sample_list[0][1]
    new_sample[0][1] = sample_list[1][1]
    new_sample[1][0] = sample_list[0][0]
    new_sample[1][1] = sample_list[1][0]

    sample_list = new_sample.copy()


##########################################
def turn_arr(arr):
    new_arr = [[0 for _ in range(len(arr))] for _ in range(len(arr[0]))]

    for i in range(len(arr[0])):
        for j in range(len(arr)):
            new_arr[i][j] = arr[len(arr) - j - 1][i]

    return new_arr


##########################################
n, m, r = map(int, input().split())

arr = [list(map(int, input().split())) for _ in range(n)]

# 입력받은 리스트 구간을 1,2,3,4단위로 나누기
temp_list = [[[0 for _ in range(m//2)] for _ in range(n//2)]for _ in range(4)]

for i in range(n // 2):
    for j in range(m // 2):
        temp_list[0][i][j] = arr[i][j]

for i in range(n // 2):
    for j in range(m // 2, m):
        temp_list[1][i][j - m // 2] = arr[i][j]

for i in range(n // 2, n):
    for j in range(m // 2):
        temp_list[2][i - n // 2][j] = arr[i][j]

for i in range(n // 2, n):
    for j in range(m // 2, m):
        temp_list[3][i - n // 2][j - m // 2] = arr[i][j]


# for i in range(4):
#     for j in temp_list[i]:
#         print(j)
#
#     print("#"*20)

##########################################
# 명령 입력받기
order = list(map(int, input().split()))

# 전체 배열을 돌리지 않고, 단순한 형태를 돌려서 결과만 복원하기
sample_list = [[0, 1], [2, 3]]
fun_list = [0, cal_1, cal_2, cal_3, cal_4, cal_5, cal_6]

result = [False, False, 0]

# 명령 수행
for i in order:
    fun_list[i]()

##########################################
# 결과 복원
# 상하 반전
if result[0]:
    for i in range(4):
        temp_list[i].reverse()


# 좌우 반전
if result[1]:
    for i in range(4):
        for j in range(len(temp_list[i])):
            temp_list[i][j].reverse()

# 배열 회전
for _ in range(result[2]):
    for i in range(4):
        temp_list[i] = turn_arr(temp_list[i])


answer = []

answer.extend(deepcopy(temp_list[sample_list[0][0]]))
answer.extend(deepcopy(temp_list[sample_list[1][0]]))

for i in range(len(answer) // 2):
    answer[i].extend(temp_list[sample_list[0][1]][i])
    answer[len(answer) // 2 + i].extend(temp_list[sample_list[1][1]][i])

for i in answer:
    print(*i)












