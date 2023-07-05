import sys
input = sys.stdin.readline
#########################################################
#데이터 입력받기
n = int(input())

#########################################################
a = [0] * (n+1)
for i in range(1,n):
    if i ** 2 > n:
        break

    count = 0
    num = 0
    for j in range(i**2,n+1):
        a[j] = count + a[num]
        num = (num+1)%(i**2)
        if j == (count+1) * i*i:
            count += 1



print(a[n])
