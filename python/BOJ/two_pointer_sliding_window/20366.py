import sys
input = sys.stdin.readline
##########################################

n = int(input())

snow = list(map(int, input().split()))

snow.sort()

answer = int(10e9)

# 안나의 눈사람을 i,j로 결정
for i in range(n-3):
    for j in range(i+3, n):
        anna_snowman = snow[i] + snow[j]

        # 엘사의 눈사람은 k,l로 결정
        k = i+1
        l = j-1

        # i~j의 사이에서 k == l이 될때까지
        while True:
            if k == l:
                break

            # 계속해서 차이 비교
            elsa_snowman = snow[k] + snow[l]
            check = anna_snowman - elsa_snowman

            # 양수이면 엘사의 눈사람이 커지게
            if check > 0:
                k += 1

            # 음수이면 엘사의 눈사람이 작아지게
            elif check < 0:
                l -= 1

            # 같으면 0출력후 실행 종료
            elif check == 0:
                print(0)
                exit()

            # 절대값 처리후 결과 갱신
            check = check if check > 0 else -check
            answer = min(answer, check)

print(answer)

