import sys


if __name__ == "__main__":
    n, k = map(int, sys.stdin.readline().split())
    ropes = []
    for i in range(n):
        ropes.append(int(sys.stdin.readline()))
    right = sum(ropes) // k
    left = 0
    while right - left > 1:
        mid = left + (right - left) // 2
        my_k = sum([i // mid for i in ropes])
        if my_k < k:
            right = mid
        else:
            left = mid
    print(left)

