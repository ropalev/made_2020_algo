import sys

PRIME = 3882959


class Set:

    def __init__(self, a, size):
        self.arr = ["e" for i in range(size)]
        self.rip = 0
        self.fill = 0
        self.a = a
        self.size = size

    def insert(self, value):

        self.rehash()
        exist, i = self.exist(value)
        if exist:
            return True
        self.arr[i] = value
        self.fill += 1

    def rehash(self):
        if self.rip + self.fill > 0.5 * self.size:
            if self.fill > 0.25 * self.size:
                self.a += self.fill % self.size
                self.size *= 2
                copy_arr = self.arr
                self.arr = ["e" for i in range(self.size)]
                self.fill = 0
                self.rip = 0
                for value in copy_arr:
                    if value != "r" and value != "e":
                        self.insert(value)
            else:
                self.a += self.fill % self.size
                self.size = self.size // 2
                copy_arr = self.arr
                self.fill = 0
                self.rip = 0
                self.arr = ["e" for i in range(self.size)]
                for value in copy_arr:
                    if value != "r" and value != "e":
                        self.insert(value)

    def delete(self, value):
        exist, i = self.exist(value)
        if not exist:
            return
        self.arr[i % self.size] = "r"
        self.rip += 1
        self.fill -= 1

    def hash(self, value):
        return (self.a * value % PRIME) % self.size

    def exist(self, value):
        i = self.hash(value)

        if self.arr[i] == value:
            return True, i
        while self.arr[i % self.size] != "e":
            if self.arr[i % self.size] == value:
                return True, i
            i = i + 1
        return False, i % self.size


if __name__ == "__main__":
    my_set = Set(7,1000)
    ans = []
    for line in sys.stdin.read().splitlines():
        if line.split()[0] == "insert":
            my_set.insert(int(line.split()[1]))
        elif line.split()[0] == "exists":
            if my_set.exist(int(line.split()[1]))[0]:
                ans.append("true")
            else:
                ans.append("false")
        elif line.split()[0] == "delete":
            my_set.delete(int(line.split()[1]))
    sys.stdout.buffer.write("\n".join(ans).encode())
