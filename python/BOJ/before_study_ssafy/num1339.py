import sys
input = sys.stdin.readline
########################################
#데이터 입력받기
n = int(input())

data = []

for _ in range(n):
    input_data = list(input())
    input_data.pop(-1)
    for alpha in range(len(input_data)):
        num = ord(input_data[alpha]) - ord('A')
        input_data[alpha] = num
    data.append(input_data[:])

########################################
alphabet = [0] * 26

for i in range(n):
    for j in range(len(data[i])):
        alphabet[data[i][j]] += 10 ** (len(data[i]) -1 - j)

alphabet.sort(reverse= True)

answer = 0
temp = 9

for i in range(10):
    answer += alphabet[i] * temp
    temp -= 1

print(answer)





























