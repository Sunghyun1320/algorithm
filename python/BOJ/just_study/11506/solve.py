import sys
sys.stdin = open("input.txt", encoding='UTF-8')
##############################################
while True:
    string = input().rstrip()

    if string == ".":
        break

    for char in string:
        if char in "占쏙옙":
            continue

        print(char, end = "")

    print()

string = "占쏙옙"

print(string.encode("KS X 1001"))
print()

key = b"\xef\xbf\xbd\xef\xbf\xbd"

print(key.decode("UTF-8"))
