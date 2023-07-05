import sys
#import heapq
input = sys.stdin.readline
##################################################

n = int(input())
A = []
B = []
C = []
D = []

# 데이터를 입력받아 A,B,C,D에 저장
for _ in range(n):
    a, b, c, d = map(int, input().split())

    A.append(a)
    B.append(b)
    C.append(c)
    D.append(d)


ab = {}
cd = []

#####################################################################
for i in range(n):
    for j in range(n):
        ab[A[i] + B[j]] = ab.get(A[i] + B[j], 0) + 1
        cd.append(C[i] + D[j])

answer = 0
for i in cd:
    answer += ab.get(-i, 0)

print(answer)



#####################################################################
# # ab와 cd에 값 집어 넣기
# for i in range(n):
#     for j in range(n):
#         heapq.heappush(ab, A[i]+B[j])
#         heapq.heappush(cd, -(C[i] + D[j]))
#
# # ab와 cd에서 값을 하나씩 꺼내며 합쳐보기
# answer = 0
# min_ab = heapq.heappop(ab)
# max_cd = -heapq.heappop(cd)
#
# # 최소 힙이 빌 때 까지 반복
# while ab:
#     # 합한 값이 양수면 최대 힙에서 추출(값 감소시키기)
#     if max_cd + min_ab > 0:
#         max_cd = -heapq.heappop(cd)
#
#     # 합한 값이 음수면 최소 힙에서 추출(값 증가 시키기)
#     elif max_cd + min_ab < 0:
#         min_ab = heapq.heappop(ab)
#
#     # 합이 0이면 결과 +1 해주고, 최소 힙에서 추출
#     # 최소힙에서 추출하든 최대 힙에서 추출하든 상관은 없지만
#     # 난 최소힙에서 추출
#     elif max_cd + min_ab == 0:
#         answer += 1
#         min_ab = heapq.heappop(ab)
#
# # ab의 마지막 값과 남은 cd의 값을 순차적으로 합함
# # 근데 만약 음수가 되면 값은 계속 작아지므로 break
# while cd:
#     if max_cd + min_ab > 0:
#         max_cd = -heapq.heappop(cd)
#
#     elif max_cd + min_ab == 0:
#         answer += 1
#         max_cd = -heapq.heappop(cd)
#
#     elif max_cd + min_ab < 0:
#         break
#
# print(answer)
