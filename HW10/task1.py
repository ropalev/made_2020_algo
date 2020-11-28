from sys import setrecursionlimit
import threading
import sys


def dfs(v, visited, graph, cnt):
    visited[v] = cnt
    for w in graph[v]:
        if visited[w] == False:  # посещён ли текущий сосед?
            dfs(w, visited, graph, cnt)

def main():
    n, m = map(int, sys.stdin.readline().split())
    graph = [[] for _ in range(n)]
    visited = [False] * n
    while m:
        v, u = map(int, sys.stdin.readline().split())
        graph[v - 1].append(u - 1)
        m -= 1
    cnt = 0
    for v in range(n):
        if visited[v] == False:
            cnt += 1
            dfs(v, visited, graph, cnt)
    print(*visited)


if __name__ == "__main__":
    main()

setrecursionlimit(10 ** 9)
threading.stack_size(2 ** 26)  # лучше использовать именно эту константу
thread = threading.Thread(target=main)
thread.start()



