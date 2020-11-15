import random
import sys

SEPARATOR = "\n"
UNICODE = "utf-8"
MAX_PRIOR = 1000

class Node(object):
    def __init__(self, key, prior):
        self.key = key
        self.prior = prior
        self.parent = None
        self.l = None
        self.r = None


class Treap(object):
    nodes = set()

    @staticmethod
    def gen():
        return random.randint(1, MAX_PRIOR)

    def __init__(self):
        self.root = None

    def split(self, t, key):
        if t is None:
            return (None, None)
        if key < t.key:
            l, t.l = self.split(t.l, key)
            r = t
            return (l, r)
        else:
            t.r, r = self.split(t.r, key)
            l = t
            return (l, r)

    def merge(self, l, r):
        if l is None:
            return r
        elif r is None:
            return l
        elif l.prior > r.prior:
            l.r = self.merge(l.r, r)
            return l
        else:
            r.l = self.merge(l, r.l)
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
        if key not in self.nodes:
            return
        self.nodes.remove(key)
        l, r = self.split(self.root, key)
        l1, _ = self.split(l, key - 1)
        self.root = self.merge(l1, r)

    def get_height(self, t):
        if t is None:
            return 0
        ans = 1
        ans = max(ans, self.get_height(t.l) + 1)
        ans = max(ans, self.get_height(t.r) + 1)
        return ans

    def pr(self, t):
        if t is None:
            return
        if t.l:
            self.pr(t.l)
        print(t.key, end=" ")
        if t.r:
            self.pr(t.r)


if __name__ == "__main__":
    treap = Treap()
    data = sys.stdin.buffer.readlines()
    result_exists = []
    n_operations = len(data)
    for i in range(n_operations):
        command, value = data[i].decode(UNICODE).split()
        if command == "insert":
            treap.insert(int(value))
        elif command == "delete":
            treap.remove(int(value))
        elif command == "exists":
            result_exists.append(treap.find(treap.root, int(value)))
        elif command == "next":
            result_exists.append(treap.next(int(value)))
        elif command == "prev":
            result_exists.append(treap.prev(int(value)))
    encoded_array = (SEPARATOR.join(result_exists)).encode(UNICODE)
    sys.stdout.buffer.write(encoded_array)
