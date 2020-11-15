# Python program to find the smallest value
# greater than or equal to N

class Node:
    def __init__(self, vales: int):
        self.data = vales
        self.left = None
        self.right = None


# To create new BST Node
    def createNode(Node: int):
        temp = Node()
        temp.data = Node
        temp.left = temp.right = None
        return temp

class BST:
    def __init__(self):
        self.root = None

    def insert(self, value: int) -> None:
        if not self.root:
            self.root = Node(value)
            return
        node = self.root
        while True:
            if node.data > value:
                if node.left:
                    node = node.left
                else:
                    node.left = Node(value)
                    return
            elif node.data < value:
                if node.right:
                    node = node.right
                else:
                    node.right = Node(value)
                    return
            else:
                return

    def exist(self, value: int):
        if not self.root:
            return None
        node = self.root
        while node:
            if node.data == value:
                return True
            elif node.data > value:
                if node.left:
                    node = node.left
                else:
                    break
            if node.data < value:
                if node.right:
                    node = node.right
                else:
                    break
        return False

    def findNext(self, node):
        if node.right != None:
            return findMostLeft(node.right)
        else:
            parent = node.parent
            while parent != None:
                if parent.leftChild == node:
                    break
                node = parent
                parent = node.parent
            return parent


if __name__ == "__main__":
    tree = BST()
    tree.insert(3)
    tree.insert(5)
    tree.insert(1)
    tree.insert(-1)
    tree.insert(0)
    tree.insert(4)
    tree.insert(11)
    tree.insert(7)
    tree.insert(6)
    print(tree.exist(2))
    print(tree.exist(11))

