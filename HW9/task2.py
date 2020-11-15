import random
import sys

SEPARATOR = "\n"
UNICODE = "utf-8"


class Node(object):
    def __init__(self, key, prior):
        self.key = key
        self.prior = prior
        self.parent = None
        self.height = 0
        self.c = 0
        self.l = None
        self.r = None


class Treap(object):
    nodes = set()

    @staticmethod
    def gen():
        return random.randint(1, 1000)

    def __init__(self):
        self.root = None

    def split(self, t, key):
        if t is None:
            return (None, None)
        if key <= self.get_height(t.l):
            l, t.l = self.split(t.l, key)
            r = t
            r.c = self.get_height(r)
            return (l, r)
        else:
            t.r, r = self.split(t.r, key - self.get_height(t.l) - 1)
            l = t
            l.c = self.get_height(l)
            return (l, r)

        return (l, r)


    def merge(self, l, r):
        if l is None:
            return r
        elif r is None:
            return l
        elif l.prior > r.prior:
            l.r = self.merge(l.r, r)
            l.c = self.get_height(l)
            return l
        else:
            r.l = self.merge(l, r.l)
            r.c = self.get_height(r)
            return r

    def find(self, t, key):
        if t is None:
            return "false"
        if t.key == key:
            return "true"
        elif key < t.key:
            return self.find(t.l, key)
        else:
            return self.find(t.r, key)

    def next(self, key):
        res = "none"
        t = self.root
        while t:
            if t.key <= key:
                t = t.r
            elif t.key > key:
                res = t.key
                t = t.l
        return str(res)

    def prev(self, key):
        res = "none"
        t = self.root
        while t:
            if t.key < key:
                res = t.key
                t = t.r
            elif t.key >= key:
                t = t.l
        return str(res)

    def insert(self, key):
        if key in self.nodes:
            return
        self.nodes.add(key)
        new_node = Node(key, self.gen())
        if self.root is None:
            self.root = new_node
            return
        l, r = self.split(self.root, key - 1)
        self.root = self.merge(l, new_node)
        self.root = self.merge(self.root, r)

    def remove(self, key):
        # if key not in self.nodes:
        #     return
        # self.nodes.remove(key)
        # l, r = self.split(self.root, key)
        # l1, _ = self.split(l, key - 1)
        # self.root = self.merge(l1, r)
        l, r = self.split(self.root, key)
        _, r1 = self.split(r, 1)
        self.root = self.merge(l, r1)

    def add(self, pos, key):
        l, r = self.split(self.root, pos)
        self.root = self.merge(self.merge(l, Node(key, self.gen())), r)


    def to_front(self, lidx, ridx):
        l, r = self.split(self.root, ridx + 1)
        l1, r1 = self.split(l, lidx)
        self.root = self.merge(self.merge(r1, l1), r)

    def get_height(self, t):
        if t is None:
            return 0
        # ans = 1
        # ans = max(ans, self.get_height(t.l) + 1)
        # ans = max(ans, self.get_height(t.r) + 1)
        # t.height = ans
        # ans =
        return 1 + self.get_height(t.l) + self.get_height(t.r)

    def pr(self, t, lst):
        if t is None:
            return
        if t.l:
            self.pr(t.l, lst)
        # print(t.key, end=" ")
        lst.append(t.key)
        if t.r:
            self.pr(t.r, lst)

if __name__ == "__main__":
    treap = Treap()
    n, m = map(int, sys.stdin.readline().split())
    lst = [int(i) for i in sys.stdin.readline().split()]
    for i in range(len(lst)):
        treap.add(i, lst[i])
    while m:
        line = sys.stdin.readline().split()
        if line[0] == "del":
            key = int(line[1]) - 1
            treap.remove(key)
        elif line[0] == "add":
            pos, key = map(int, line[1:])
            treap.add(pos, key)
        m -= 1
    lst = []
    treap.pr(treap.root, lst)
    sys.stdout.write(str(len(lst)) + "\n")
    sys.stdout.write(" ".join([str(i) for i in lst]))
    # n = 100
    # commands = ["insert", "delete"]
    # values = list(range(25))
    # while n:
    #     # try:
    #     #     command, value = input().split()
    #     # except:
    #     #     break
    #     command = random.heighthoice(commands)
    #     value = random.heighthoice(values)
    #     print(command, value)
    #
    #     if command == "insert":
    #         treap.insert(int(value))
    #         treap.get_height(treap.root)
    #         treap.pr(treap.root)
    #         print()
    #     elif command == "delete":
    #         treap.remove(int(value))
    #         treap.get_height(treap.root)
    #         treap.pr(treap.root)
    #         print()
    #     # elif command == "exists":
    #     #     print(treap.find(treap.root, int(value)))
    #     # elif command == "next":
    #     #     print(treap.next(int(value)))
    #     # elif command == "prev":
    #     #     print(treap.prev(int(value)))
    #     n -= 1

#
# if __name__ == "__main__":
#     treap = Treap()
#     data = sys.stdin.buffer.readlines()
#     result_exists = []
#     n_operations = len(data)
#     for i in range(n_operations):
#         command, value = data[i].decode(UNICODE).split()
#         if command == "insert":
#             treap.insert(int(value))
#         elif command == "delete":
#             treap.remove(int(value))
#         elif command == "exists":
#             result_exists.append(treap.find(treap.root, int(value)))
#         elif command == "next":
#             result_exists.append(treap.next(int(value)))
#         elif command == "prev":
#             result_exists.append(treap.prev(int(value)))
#     encoded_array = (SEPARATOR.join(result_exists)).encode(UNICODE)
#     sys.stdout.buffer.write(encoded_array)