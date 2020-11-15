
import random


class Treap:
    def __init__(self, val, priority):
        self.val = val
        self.priority = priority
        self.left = None
        self.right = None
        self.size = 1
        self.reverse = False
        self.segment_sum = val

    def copy(self, new_node):

        self.val = new_node.val
        self.priority = new_node.priority
        self.left = new_node.left
        self.right = new_node.right
        self.size = new_node.size
        self.segment_sum = new_node.segment_sum

    @staticmethod
    def update_segment_sum(node):
        if node is not None:
            left_sum = 0 if node.left is None else node.left.segment_sum
            right_sum = 0 if node.right is None else node.right.segment_sum
            node.segment_sum = left_sum + node.val + right_sum

    @staticmethod
    def update_size(node):
        if node is not None:
            left_size = 0 if node.left is None else node.left.size
            right_size = 0 if node.right is None else node.right.size
            node.size = left_size + 1 + right_size

    @staticmethod
    def get_left_size(node):
        return 0 if node.left is None else node.left.size


class Treap:
    def __init__(self, array=None, root=None):
        if root is not None:
            self._root = root
        elif array is not None:
            self._root = Treap.innit(array=array)
        else:
            self._root = None

    def divide(self, index: int):
        first_root, second_root = Treap.split(self._root, index)
        return Treap(root=first_root), Treap(root=second_root)

    def union(self, tree):
        root = Treap.merge(self._root, tree._root)
        return Treap(root=root)

    def __setitem__(self, key, value):
        node = Treap(value, random.random())
        self._root = Treap.insert(self._root, node, key)

    def __getitem__(self, item):
        item = Treap.get_item(self._root, item)
        return None if item is None else item.val

    def size(self):
        return Treap.get_size(self._root)

    def print(self, list=None, console_print=True):
        Treap.print_tree(self._root, list, console_print=console_print)

    def get_sum(self, left, right):
        return Treap.get_segment_sum(self._root, left, right)

    def erase(self, index):
        Treap.delete(self._root, index)

    def invert(self, left, right):
        Treap.reverse(self._root, left, right)

    @staticmethod
    def get_size(tree: Treap):
        return tree.size

    @staticmethod
    def get_item(tree: Treap, index: int, add: int = 0):
        if tree is None:
            return None
        current_key = add + Treap.get_left_size(tree)
        if current_key == index:
            return tree

        if current_key < index:
            new_add = add + 1 + Treap.get_left_size(tree)
            return Treap.get_item(tree.right, index, new_add)
        else:
            return Treap.get_item(tree.left, index, add)

    @staticmethod
    def reverse(tree, left, right):
        if right < left:
            left, right = right, left
        first_tree, second_tree = Treap.split(tree, left)
        second_tree, third_tree = Treap.split(second_tree, right - left + 1)
        second_tree.reverse = bool(True ^ second_tree.reverse)
        Treap.merge(first_tree, Treap.merge(second_tree, third_tree))

    @staticmethod
    def push_reverse(tree: Treap):
        if tree is not None:
            if tree.reverse:
                tree.left, tree.right = tree.right, tree.left
                tree.reverse = False
                if tree.left is not None:
                    tree.left.reverse = bool(True ^ tree.left.reverse)
                if tree.right is not None:
                    tree.right.reverse = bool(True ^ tree.right.reverse)


    @staticmethod
    def get_segment_sum(tree: Treap, left: int, right: int):
        if right < left:
            left, right = right, left
        first_tree, second_tree = Treap.split(tree, left)
        second_tree, third_tree = Treap.split(second_tree, right - left + 1)
        result = second_tree.segment_sum
        tree = Treap.merge(Treap.merge(first_tree, second_tree), third_tree)
        return result

    @staticmethod
    def innit(array=None) -> Treap:
        tree = None
        for index, elem in enumerate(array):
            node = Treap(elem, random.random())
            tree = Treap.insert(tree, node, index)
        return tree

    @staticmethod
    def insert(origin_tree: Treap, node: Treap, index: int):
        first_tree, second_tree = Treap.split(origin_tree, index)
        return Treap.merge(Treap.merge(first_tree, node), second_tree)

    @staticmethod
    def delete(tree, index, add=0):
        """
        TODO нужен ли здесь push_reverse? вот в чем вопрос
        """
        if tree is None:
            return
        current_key = add + Treap.get_left_size(tree)
        new_add = current_key + 1
        left_key = float("inf")
        right_key = float("inf")
        if tree.left is not None:
            left_key = add + Treap.get_left_size(tree.left)
        if tree.right is not None:
            right_key = new_add + Treap.get_left_size(tree.right)
        if current_key == index:
            try:
                new_node = Treap.merge(tree.left, tree.right)
                tree.copy(new_node)
                Treap.update_size(tree)
                Treap.update_segment_sum(tree)
            except Exception:
                raise Exception("Delete last item in array")

        elif left_key == index:
            new_node = Treap.merge(tree.left.left, tree.left.right)
            tree.left = new_node

            Treap.update_size(tree)
            Treap.update_segment_sum(tree)

        elif right_key == index:
            new_node = Treap.merge(tree.right.left, tree.right.right)
            tree.right = new_node

            Treap.update_size(tree)
            Treap.update_segment_sum(tree)

        else:
            if current_key < index:
                Treap.delete(tree.right, index, new_add)
                Treap.update_size(tree)
                Treap.update_segment_sum(tree)
            else:
                Treap.delete(tree.left, index, add)
                Treap.update_size(tree)
                Treap.update_segment_sum(tree)


        # if current_key < index:
        #     return Treap.get_item(tree.right, index, new_add)
        # else:
        #     return Treap.get_item(tree.left, index, add)
        # node = Treap.get_item(tree, index)
        # new_node = Treap.merge(node.left, node.right)
        # if new_node is None:
        #     node = None
        #     del node
        # else:
        #     node.copy(new_node)

    @staticmethod
    def split(tree: Treap, key: int, add: int=0):

        if tree is None:
            return None, None

        Treap.push_reverse(tree)
        current_key = add + Treap.get_left_size(tree)
        if current_key < key:
            new_add = add + 1 + Treap.get_left_size(tree)
            first_tree, second_tree = Treap.split(tree.right, key, new_add)
            tree.right = first_tree
            Treap.update_size(tree)
            Treap.update_size(second_tree)
            Treap.update_segment_sum(tree)
            Treap.update_segment_sum(second_tree)

            return tree, second_tree
        else:
            first_tree, second_tree = Treap.split(tree.left, key, add)
            tree.left = second_tree
            Treap.update_size(tree)
            Treap.update_size(first_tree)
            Treap.update_segment_sum(tree)
            Treap.update_segment_sum(first_tree)

            return first_tree, tree

    @staticmethod
    def merge(first_tree: Treap, second_tree: Treap) -> Treap:
        """
        сливает два дерева только если все ключи дерева first_tree меньше
        ключей дерева second_tree
        """
        Treap.push_reverse(first_tree)
        Treap.push_reverse(second_tree)
        if first_tree is None:
            return second_tree
        if second_tree is None:
            return first_tree

        if first_tree.priority > second_tree.priority:
            first_tree.right = Treap.merge(first_tree.right, second_tree)
            Treap.update_size(first_tree)
            Treap.update_segment_sum(first_tree)
            return first_tree
        else:
            second_tree.left = Treap.merge(first_tree, second_tree.left)
            Treap.update_size(second_tree)
            Treap.update_segment_sum(second_tree)
            return second_tree


    @staticmethod
    def print_tree(tree: Treap, list=None, console_print=True):
        if tree is None:
            return
        Treap.push_reverse(tree)
        Treap.print_tree(tree.left, list=list, console_print=console_print)
        if console_print:
            print("Node with value: %s and priority: %s\n" % (tree.val, tree.priority))
        if list is not None:
            list.append(tree.val)
        Treap.print_tree(tree.right, list=list, console_print=console_print)


if __name__ == "__main__":
    treap = Treap(4,3)

    treap = Treap.innit([1,5,7,6,4,3,2])
    Treap.print_tree(treap)
