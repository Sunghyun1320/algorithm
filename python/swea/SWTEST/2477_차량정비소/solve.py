import sys
sys.stdin = open("input.txt")
##############################################
from collections import deque
T = int(input())

for test_case in range(1, T+1):
    N, M, K, A, B = map(int, input().split())
    # 정비소가 1번부터 번호지만 나는 인덱스로 0번부터 할거라서 -1
    A -= 1
    B -= 1
    a_list = list(map(int, input().split()))
    b_list = list(map(int, input().split()))
    k_list = list(map(int, input().split()))

    # 시작할 때 +1 할꺼기 때문에 0부터 시작하기 위한 -1부터
    time = -1

    # 접수 창구
    a = [0 for _ in range(N)]
    # 정비 창구
    b = [0 for _ in range(M)]

    # 대기 인원들
    waiting_a = deque()
    waiting_b = deque()

    # 방문자들 번호
    visiter_num = 0

    # A,B를 방문한 방문자들 번호
    answer = []
    # 정비를 마친 사람들 수 : 반복 종료를 위한 카운팅
    clear_count = 0
    while True:
        # 시간이 지났다.
        time += 1

        # 접수창구가
        for i in range(N):
            # 빈칸이면 처리 안함
            if a[i] == 0:
                continue

            # 남은 업무시간 -1씩
            a[i][1] -= 1

            # 처리 되었다면, b를 기다리는 사람으로 보내고
            # 접수창구 번호를 기록 함
            # 그리고 빈칸으로 만듬
            if a[i][1] == 0:
                waiting_b.append([a[i][0], i])
                a[i] = 0

        # 정비 창구 사람들의
        for i in range(M):
            # 빈칸이면 처리 안 함
            if b[i] == 0:
                continue

            # 남은 업무시간 -1씩
            b[i][1] -= 1

            # 처리 되었다면, 처리된 사람수 + 1
            # 빈 창구로 만듬
            if b[i][1] == 0:
                clear_count += 1
                b[i] = 0

        if clear_count == K:
            break

        # 고객 번호중에
        while visiter_num < K:
            # 현재 도착한 사람이 있으면
            if k_list[visiter_num] == time:
                # a대기 인원에 고객 번호 추가하고
                waiting_a.append(visiter_num)
                # 접수번호 + 1
                visiter_num += 1

            else:
                break

        # 모든 접수 창구에 대해서
        for i in range(N):
            # 빈칸이 있고, 대기 인원이 있다면
            if a[i] == 0 and waiting_a:
                # 대기 인원의 고객 번호를 가져오고,
                # 업무시간 적용
                a[i] = [waiting_a.popleft(), a_list[i]]

        # 모든 정비 창구에 대해서
        for i in range(M):
            # 빈칸이 있고, 대기인원이 있을 때
            if b[i] == 0 and waiting_b:
                # 만약 A와 B를 방문한 사람이면
                if waiting_b[0][1] == A and i == B:
                    # 정답에 고객 번호 추가
                    # 고객번호를 0번부터 부여했으므로 저장시 + 1
                    answer.append(waiting_b[0][0] + 1)

                # b에서 고객번호만 빼오고 업무시간 적용
                b[i] = [waiting_b.popleft()[0], b_list[i]]

    # 계산 결과
    # 아무도 없다면 -1
    if len(answer) == 0:
        answer = [-1]

    print(f"#{test_case} {sum(answer)}")



