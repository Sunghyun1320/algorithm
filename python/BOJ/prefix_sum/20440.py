import sys
input = sys.stdin.readline
###########################################
n = int(input())

# 누적합을 위한 딕셔너리
mos_enter_exit = {}

# 특정 시간에 모기의 출입을 관리하도록 갱신
for _ in range(n):
    enter, exit_ = map(int, input().split())

    mos_enter_exit[enter] = mos_enter_exit.get(enter, 0) + 1
    mos_enter_exit[exit_] = mos_enter_exit.get(exit_, 0) - 1


# 결과 값들
max_mos_count = -1
max_mos_time = [None, None]

# 최대값 구간이 2개 이상일때를 대비한 체크 변수
check = False

# 시간순서대로 탐색
mos = sorted(mos_enter_exit.keys())
sum_mos = 0


for time in mos:
    sum_mos += mos_enter_exit[time]

    # 가장 많은 모기가 잇는 시간대 중 가장 앞순서의 시간을 기록하기 위해
    # 등호 X
    if sum_mos > max_mos_count:
        max_mos_count = sum_mos
        max_mos_time[0] = time
        check = True

    elif sum_mos < max_mos_count and check:
        max_mos_time[1] = time
        check = False

print(max_mos_count)
print(max_mos_time[0], max_mos_time[1])