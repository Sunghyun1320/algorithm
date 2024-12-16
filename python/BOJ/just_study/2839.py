n = int(input())
if n == 1 or n == 2 or n == 4 or n == 7:
    print(-1)
    exit()


count = (n // 15) * 3

n %= 15

if n == 1:
    print(count - 3 + 4)
elif n == 2 :
    print(count - 3 + 5)
elif n == 4:
    print(count - 3 + 5)
elif n == 7:
    print(count - 3 + 6)

elif n == 0:
    print(count)

elif n == 3 or n == 5:
    print(count + 1)

elif n == 6 or n == 8 or n == 10:
    print(count + 2)

elif n == 9 or n == 11 or n == 13:
    print(count + 3)

elif n == 12 or n == 14:
    print(count + 4)