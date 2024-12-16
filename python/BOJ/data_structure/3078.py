import sys
input_ = sys.stdin.readline
##########################################
n, m = map(int, input().split())

students = [len(input_().rstrip()) for _ in range(n)]

# k범위 이내에서 학생이름의 길이가 같은 학생의 수
# 이름길이가 3인 학생들의수가 len_list[3]에 저장됨
len_list = [0] * 21

# 초기 1~m번의 범위 학생들 수 이름별로 정리
for i in range(m):
    len_list[students[i]] += 1

result = 0

# n-m번까지에서 좋은 친구의 수 찾기
# n-m번 부터는 범위가 m보다 작아짐
for i in range(n-m):
    j = i+m
    len_list[students[j]] += 1
    len_list[students[i]] -= 1
    result += len_list[students[i]]

# n-m번 학생부터 나머지 학생들간의 좋은 친구 수 찾기
for i in range(n-m, n):
    len_list[students[i]] -= 1
    result += len_list[students[i]]

print(result)




