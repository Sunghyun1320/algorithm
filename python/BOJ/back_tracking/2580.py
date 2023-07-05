import sys
input = sys.stdin.readline
###########################################
def fill_blank(depth, n):
    # 최대 깊이 도달시 스토쿠 완성.
    # 출력후 코드 종료
    if depth == n:
        for i in sudoku:
            print(*i)
        # print("#" * 30)
        # return
        exit()

    # 빈칸의 좌표는 현재의 깊이
    x, y = blank[depth]
    for i in range(9):
        if check_num[x][y][i]:
            continue

        sudoku[x][y] = i+1

        # 기존의 값 저장
        # 저장 하면서 바꿀경우 바뀐값이 저장되는 경우가 있음
        # 저장 후 바꿀것
        temp = []
        for j in range(9):
            temp.append(check_num[x][j][i])
            temp.append(check_num[j][y][i])
            # check_num[x][j][i] = True
            # check_num[j][y][i] = True

        for j in range(3):
            for k in range(3):
                nx = x//3 * 3
                ny = y//3 * 3

                temp.append(check_num[nx + j][ny + k][i])
                # check_num[nx + j][ny + k][i] = True

##################################################
        # 그 다음 방문처리
        for j in range(9):
            check_num[x][j][i] = True
            check_num[j][y][i] = True

        for j in range(3):
            for k in range(3):
                nx = x//3 * 3
                ny = y//3 * 3

                check_num[nx + j][ny + k][i] = True
#################################################
        # 현재 상태로 다음 빈칸 채우기
        fill_blank(depth+1, n)

        # 기존 값 복원
        sudoku[x][y] = 0
        count = 0

        for j in range(9):
            check_num[x][j][i] = temp[count]
            count += 1
            check_num[j][y][i] = temp[count]
            count += 1

        for j in range(3):
            for k in range(3):
                nx = x // 3 * 3
                ny = y // 3 * 3

                check_num[nx + j][ny + k][i] = temp[count]
                count += 1


###########################################
sudoku = [list(map(int, input().split())) for _ in range(9)]

blank = []
count_blank = 0
check_num = [[[False for _ in range(9)] for _ in range(9)] for _ in range(9)]

for i in range(9):
    for j in range(9):
        # 빈칸인 경우 빈칸리스트에 추가후 빈칸 개수 +1
        if sudoku[i][j] == 0:
            count_blank += 1
            blank.append([i, j])
            continue

        # 같은 열, 같은 행에 해당 숫자 사용 처리
        for k in range(9):
            check_num[i][k][sudoku[i][j] - 1] = True
            check_num[k][j][sudoku[i][j] - 1] = True

        # 같은 영역에서 숫자 사용처리
        for k in range(3):
            for l in range(3):
                x = i//3 * 3
                y = j//3 * 3

                check_num[x + k][y + l][sudoku[i][j] - 1] = True

# 빈칸채우기 실행
fill_blank(0, count_blank)
