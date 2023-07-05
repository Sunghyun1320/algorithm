import sys
input = sys.stdin.readline
######################################################
# prime_num = [False for _ in range(10000)]
#
# for i in range(2, int(10000)):
#     if prime_num[i]:
#         continue
#
#     for j in range(i+i, int(10000), i):
#         prime_num[j] = True
# 소수를 판단해서 결과를 반환하는 함수
def is_prime(x):
    i = 2
    while True:
        if i ** 2 >= x:
            return True

        if x % i == 0:
            return False

        i += 1
#######################################################
def solve(n, num, depth = 1):
    # 2자리 수부터는 1,3,7,9만 올 수 있음
    # 짝수
    num_list = [1, 3, 7, 9]
    if n == depth:
        print(num)
        return

    for i in range(4):
        temp = 10*num + num_list[i]
        if is_prime(temp):
            solve(n, 10*num + num_list[i], depth + 1)


#######################################################
n = int(input())

# 첫번째 수로는 소수만 가능
num_list = [2, 3, 5, 7]

for num in num_list:
    solve(n, num)

