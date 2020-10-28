import sys





if __name__ == "__main__":
    n, k = map(int, input().split())
    field = []
    for i in range(n):
        field.append(input().split())
    res = [[0 for i in range(k)] for j range(n)]
    res[0][0] = ""
    for i in range(1,k):
        for j in range(1,n):
            if i == 0:

    print(field)
