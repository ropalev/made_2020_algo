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
    n, m = 4, 100
    lst = list(range(1, n + 1))
    for i in range(len(lst)):
        treap.add(i, lst[i])
    while m:
        l , r = random.randint(1,n) , random.randint(1, n)
        l, r = min(l,r), max(l,r)
        print(l , r)
        treap.to_front(l - 1, r - 1)
        m -= 1
        lst = []
        treap.pr(treap.root, lst)
        # print(len(lst))
        print(" ".join([str(i) for i in lst]))