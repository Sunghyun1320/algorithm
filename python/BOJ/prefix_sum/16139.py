import sys
input = sys.stdin.readline
########################################
string = input().rstrip()

q = int(input())

# 알파벳 개수를 세는 누적합
count_char_prefix = [{} for _ in range(len(string)+1)]

# 각 index별로 알파벳의 개수를 구별하여 누적합을 구함
for i in range(len(string)):
    count_char_prefix[0][string[i]] = 0
    count_char_prefix[i + 1] = count_char_prefix[i].copy()
    count_char_prefix[i+1][string[i]] = count_char_prefix[i+1].get(string[i], 0) + 1

# 개수 출력
for _ in range(q):
    char, s, e = input().split()
    s, e = int(s), int(e)
    print(count_char_prefix[e+1].get(char, 0) - count_char_prefix[s].get(char, 0))


