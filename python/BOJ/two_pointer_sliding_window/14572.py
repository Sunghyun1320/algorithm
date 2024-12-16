import sys
input = sys.stdin.readline
###########################################
# 데이터 입력받기
n, k, d = map(int, input().split())

algo = [0 for _ in range(k+1)]

student = [[] for _ in range(n)]


# n명의 학생들 데이터 입력받기
for student_num in range(n):
    # 알고있는 알고리즘의 개수와 실력
    student_data = list(map(int, input().split()))
    # 알고있는 알고리즘 리스트가 저장
    student_data.append(list(map(int, input().split())))

    # [알고리즘 개수, 실력, [알고리즘 리스트]]
    student[student_num] = student_data.copy()

# 실력 기준으로 정렬
student.sort(key = lambda x: x[1])

# 스터디원이 알고있는 모든 알고리즘
sum_know_algo = 0
# 모든 스터디원이 알고 잇는 알고리즘
sub_know_algo = 0

# 0~0번 학생까지 스터디 그룹을 생성
i = 0
j = 0
# 최대 효율을 저장할 리스트
answer = -1

while True:
    # 실력차이가 d 초과이면 j 증가 시키기
    if student[i][1] - student[j][1] > d:
        # j학생이 알고있는 알고리즘에 대해서
        for algo_num in student[j][2]:
            # 해당 알고리즘을 아는 학생 -1
            algo[algo_num] -= 1
            # 만약 그 알고리즘이 j학생만 알고잇던 알고리즘이면 모든 알고리즘 -1
            if algo[algo_num] == 0:
                sum_know_algo -= 1

        j += 1

    # 실력 차이가 d 이하이면 i번째 학생 추가하고 효율성 계산
    if student[i][1] - student[j][1] <= d:
        # 모든 스터디원이 알고있는 알고리즘은 추가될때마다 새로 새줘야됨
        sub_know_algo = 0

        # 이번 학생이 알고있는 알고리즘에 대해서
        for algo_num in student[i][2]:
            # 해당 알고리즘 아는 학생 + 1
            algo[algo_num] += 1

            # 만약 해당 알고리즘을 아는 학생수가 스터디 학생 전체인 경우
            # 모든 스터디원이 알고있는 알고리즘 개수 추가
            if algo[algo_num] == i - j + 1:
                sub_know_algo += 1

            # 해당 알고리즘이 이번에 추가된 학생만 아는 경우
            # 스터디원이 알고있는 모든 알고리즘 +1
            if algo[algo_num] == 1:
                sum_know_algo += 1

        answer = max(answer, (sum_know_algo - sub_know_algo) * (i - j + 1))

        i += 1

    # i가 n이되면 j를 증가시켜도 효율은 감소하므로 반복 멈춤
    if i == n:
        break

# 정답 출력
print(answer)







