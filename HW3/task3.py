def root_and_square(value):
    eps = 0.0000001
    left = 1
    right = value**0.5
    for i in range(999):
        mid = left + (right - left) / 2
        if ((mid**2 + mid**0.5) < value + eps) and ((mid**2 + mid**0.5) > value - eps):

            return right
        elif mid**2 + mid**0.5 > value + eps:
            right = mid
        else:
            left = mid
    return right

if __name__ == "__main__":
    c = float(input())
    print(root_and_square(c))