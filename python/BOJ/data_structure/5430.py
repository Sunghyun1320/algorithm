from collections import deque
import sys
input = sys.stdin.readline
###########################################
t = int(input())

for _ in range(t):

    p = input().rstrip()
    n = int(input())
    data = deque(input().strip("[]\n").replace(",", " ").split())
    # if data[0] == "":
    #     data = deque()

    # 리스트가 역전시켰는지 판단하는 변수
    check_reverse = False

    # 에러가 나서 끝났는지 판단하는 변수
    check_stop = False

    # 명령을 하나씩 수행
    for order in p:
        # R이면 리버스 변수만 바꾸고 다음 명령
        if order == "R":
            check_reverse = not check_reverse
            continue

        # 여기서 부터 D명령만 수행
        # 길이가 0이면 에러 출력후 에러발생켜고 명령수행 멈춤
        if len(data) == 0:
            print("error")
            check_stop = True
            break

        if check_reverse:
            data.pop()

        else:
            data.popleft()

    # 에러가 나서 멈췄으면 다음 테스트 케이스
    if check_stop:
        continue

    # 괄호 열고
    answer = "["

    # 리버스 상태에 따라서 값 추가
    if check_reverse:
        data.reverse()
        answer += ",".join(data)
    else:
        answer += ",".join(data)
    answer += "]"

    print(answer)









