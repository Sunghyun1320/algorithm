import sys
input = sys.stdin.readline
#############################################
# 1부터 10e6 + 1까지 소수를 구해서 리스트로 만듬
max_num = 10000001

num = [True for _ in range(max_num)]

prime_num = []

for i in range(2, max_num):
    if num[i]:
        prime_num.append(i)
        for j in range(i+i, max_num, i):
            num[j] = False

count_prime = len(prime_num)

# print(prime_num)
# print(prime_num[-1])
# print(count_prime)
# print(sum(prime_num))

#############################################

t = int(input())

for test_case in range(1, t+1):
    m = int(input())
    count_num = list(map(int, input().split()))
    count_num.sort(reverse = True)

    sum_prime_num = [[sum(prime_num[:count_num[i]]), 0] for i in range(m)]

    while True:
        # 총 합이 소수인지 판별
        if num[sum_prime_num[0][0]]:
            break

        # 아니면 다음 구간의 합을 구해 줌
        sum_prime_num[0][0] -= prime_num[sum_prime_num[0][1]]
        sum_prime_num[0][1] += 1

        # 모든 경우를 해 봤지만 안되는 경우
        # 가... 있나?
        if sum_prime_num[0][1] >= count_prime - count_num[0] + 1:
            break

        sum_prime_num[0][0] += prime_num[sum_prime_num[0][1] + count_num[0] - 1]


    index = 1

    while True:
        # 모든 숫자가 같아진 경우
        if index == m:
            break

        # 0의 경우
        if index == 0:
            while True:
                # 아니면 다음 구간의 합을 구해 줌
                sum_prime_num[0][0] -= prime_num[sum_prime_num[0][1]]
                sum_prime_num[0][1] += 1

                # 모든 경우를 해 봤지만 안되는 경우
                # 가... 있나?
                if sum_prime_num[0][1] >= count_prime - count_num[0] + 1:
                    break

                sum_prime_num[0][0] += prime_num[sum_prime_num[0][1] + count_num[0] - 1]

                # 총 합이 소수인지 판별
                if num[sum_prime_num[0][0]]:
                    break

            index += 1
            continue

        # 값이 같아진 경우 다음 인덱스
        if sum_prime_num[index][0] == sum_prime_num[0][0]:
            index += 1
            continue

        # 값이 더 클 경우 0번 값의 구간을 바꿔줌
        if sum_prime_num[index][0] > sum_prime_num[0][0]:
            index = 0
            continue

        # 작은경우 이번 인덱스의 구간을 바꿔줌
        if sum_prime_num[index][0] < sum_prime_num[0][0]:
            sum_prime_num[index][0] -= prime_num[sum_prime_num[index][1]]
            sum_prime_num[index][1] += 1

            # 모든 경우를 해 봤지만 안되는 경우
            # 가... 있나?
            if sum_prime_num[index][1] >= count_prime - count_num[index] + 1:
                break

            sum_prime_num[index][0] += prime_num[sum_prime_num[index][1] + count_num[index] - 1]
            continue

    print(f"Scenario {test_case}:")
    print(sum_prime_num[0][0])
    print()
