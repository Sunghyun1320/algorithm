import sys
input = sys.stdin.readline
##########################################
dx = [0, 1, 0, -1, 1, 1, -1, -1]
dy = [1, 0, -1, 0, 1, -1, 1, -1]

reward = [0, 0, 0, 1, 1, 2, 3, 5, 11]
##########################################
def dfs(x, y, depth, word, word_idx):
    if check[word_idx]:
        return

    if depth == len(word) - 1 and board[x][y] == word[depth]:
        global count, max_len_word, point
        check[word_idx] = True
        point += reward[depth + 1]
        count += 1
        if len(max_len_word) < len(word):
            max_len_word = word

        if len(max_len_word) == len(word):
            a = [max_len_word, word]
            a.sort()
            max_len_word = a[0]
        return

    if board[x][y] != word[depth]:
        return

    for dir in range(8):
        nx = x + dx[dir]
        ny = y + dy[dir]

        if nx < 0 or nx >= 4 or ny < 0 or ny >= 4 or visited[nx][ny]:
            continue

        visited[nx][ny] = True
        dfs(nx, ny, depth+1, word, word_idx)
        visited[nx][ny] = False


##########################################
n = int(input())

words = [input().rstrip() for _ in range(n)]
input()

words = list(set(words))
n = len(words)

T = int(input())
for test_case in range(T):
    point = 0
    max_len_word = ""
    count = 0

    board = [list(input().rstrip()) for _ in range(4)]
    if test_case != T-1:
        input()

    check = [False for _ in range(n)]
    visited = [[False for _ in range(4)] for _ in range(4)]
    for word_idx in range(n):
        for i in range(4):
            for j in range(4):
                visited[i][j] = True
                dfs(i, j, 0, words[word_idx], word_idx)
                visited[i][j] = False

    print(point, max_len_word, count)
