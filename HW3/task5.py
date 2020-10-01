import math


def find_minut(n, v1, v2):
    left = 1 / min(v1, v2)
    right = n * max(v1, v2)
    bias = 1 + 1 if n % 2 else 0
    while right - left > 1:
        mid = left + (right - left) // 2
        print(left, mid, right)
        res = mid * ((v2 + v1) / (v2 * v1)) + 1 / min(v1, v2)
        if res > n:
            right = mid
        elif res < n:
            left = mid
        else:
            break

    return mid + bias


if __name__ == "__main__":
    n, v1, v2 = [int(i) for i in input().split()]
    print(find_minut(n, v1, v2))
