import sys
input = sys.stdin.readline
###########################################################
#데이터 입력받기
n = int(input())

#입력된 데이터 해당리스트의 순서대로 좌석 배치
student_data = []

#좋아하는 학생정보가 인덱스로 접근가능한 자료
like_student_list = [[] for _ in range(n**2 + 1)]

#교실 상황
class_graph = [[0 for _ in range(n)] for _ in range(n)]

for _ in range(n**2):
    a = list(map(int, input().split()))
    like_student_list[a[0]] = a[1:]
    student_data.append(a[:])

###########################################################
#필요한 기본 데이터
dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]

###########################################################
#학생 배치하기
for student_num, a, b, c, d in student_data:
    like_student = [a, b, c, d]
    #만족도가 가장높은 자리의 만족도
    max_satisfied = -1
    #만족도가 가장높은 자리의 빈칸수
    this_open_sit = 0
    #최고 만족 자리
    max_satisfied_postion = [0, 0]
    #모든 좌석 탐색
    for i in range(n):
        for j in range(n):
            #빈자리가 아니면 다음 자리 탐색
            if class_graph[i][j] != 0:
                continue

            #현재 자리의 만족도
            satisfied = 0
            open_sit = 0

            #현재 자리기준 인접한 4자리 탐색
            for dir in range(4):
                nx = i + dx[dir]
                ny = j + dy[dir]

                if 0 <= nx < n and 0 <= ny < n:
                    if class_graph[nx][ny] in like_student:
                        satisfied += 1
                    elif class_graph[nx][ny] == 0:
                        open_sit += 1


            #현재자리 만족도에 따른 만족도 갱신, 자리 갱신
            #만족도가 같을경우 빈자리에 따라 갱신
            #만족도가 같은자리가 여러개일때 맨위, 최좌측인데
            #맨위, 최 좌측부터 탐색하므로 신경안씀
            if satisfied > max_satisfied:
                max_satisfied = satisfied
                max_satisfied_postion = [i, j]
                this_open_sit = open_sit

            elif satisfied == max_satisfied:
                if open_sit > this_open_sit:
                    this_open_sit = open_sit
                    max_satisfied = satisfied
                    max_satisfied_postion = [i, j]


    class_graph[max_satisfied_postion[0]][max_satisfied_postion[1]] = student_num

###########################################################
#만족도 조사
result_satisfied = 0

for i in range(n):
    for j in range(n):
        satisfied = 0
        for dir in range(4):
            nx = i + dx[dir]
            ny = j + dy[dir]

            if 0 <= nx < n and 0 <= ny < n:
                if class_graph[nx][ny] in like_student_list[class_graph[i][j]]:
                    satisfied += 1

        if satisfied == 0:
            result_satisfied += 0
        elif satisfied == 1:
            result_satisfied += 1
        elif satisfied == 2:
            result_satisfied += 10
        elif satisfied == 3:
            result_satisfied += 100
        elif satisfied == 4:
            result_satisfied += 1000

print(result_satisfied)