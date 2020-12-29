import sys

SIZE = 1000
A = 7
PRIME = 1009

class Node(object):

    def __init__(self, key=None, data=None, next_node=None):
        self.data = data
        self.key = key
        self.next_node = next_node

    def get_data(self):
        return self.data

    def get_next(self):
        return self.next_node

    def set_next(self, new_next):
        self.next_node = new_next

class LinkedList(object):
    def __init__(self, head=None):
        self.head = head

    def insert(self, data):
        new_node = Node(data)
        new_node.set_next(self.head)
        self.head = new_node

    def size(self):
        current = self.head
        count = 0
        while current:
            count += 1
            current = current.get_next()
        return count

    def search(self, data):
        current = self.head
        found = False
        while current and found is False:
            if current.get_data() == data:
                found = True
            else:
                current = current.get_next()
        if current is None:
            None
        return current

    def delete(self, data):
        current = self.head
        previous = None
        found = False
        while current and found is False:
            if current.get_data() == data:
                found = True
            else:
                previous = current
                current = current.get_next()
        if current is None:
            return None
        if previous is None:
            self.head = current.get_next()
        else:
            previous.set_next(current.get_next())


class HashMap():
    def __init__(self):
        self.arr = [None for i in range(SIZE)]
        self.size = SIZE

    def put(self, key, value):
        i = self.hash(value)
        if not self.arr[i]:
            self.arr[i] = LinkedList()
        self.arr[i].insert(value)

    def delete(self, value):
        if not self.arr[i].delete(value):
            self.arr[i] = None

    def get(self,value):
        if self.arr[i].get(value):
            self.arr[i].get(value).get_data()


    def hash(self, key):
        res = 0
        for i in str(key):
            res = (res * A + ord(i)) % PRIME
        res = res % self.size
        return int(res)
    

if __name__ == "__main__":
    my_map = HashMap()
    ans = []
    for line in sys.stdin.read().splitlines():
        if line.split()[0] == "put":
            my_map.put(line.split()[1])
        elif line.split()[0] == "get":
            if my_map.get(line.split()[1])[0]:
                ans.append("true")
            else:
                ans.append("false")
        elif line.split()[0] == "delete":
            my_map.delete(line.split()[1])
    sys.stdout.buffer.write("\n".join(ans).encode())
