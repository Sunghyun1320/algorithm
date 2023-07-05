from sys import stdin


def main():
    n, m = map(int, stdin.readline().split())
    arr = [[0] * (m + 1)] + \
          [([0] + list(map(int, stdin.readline().split()))) for _ in range(n)]

    res = -10000

    for i in range(1, n + 1):
        p = [0] * (m + 1)
        for j in range(i, n + 1):
            t = [0] * (m + 1)
            for k in range(1, m + 1):
                p[k] += arr[j][k]
                t[k] = max(t[k - 1] + p[k], p[k])
                res = max(t[k], res)

    print(res)


if __name__ == "__main__":
    main()