

# Definition for a  binary tree node
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

    def __str__(self):
        stack = [self]
        res = ''
        not_none_num = 1
        while not_none_num > 0:
            another_stack = []
            not_none_num = 0
            for node in stack:
                if node:
                    res += str(node.val) + "\t"
                    if node.left: not_none_num += 1
                    if node.right: not_none_num += 1
                    another_stack.append(node.left)
                    another_stack.append(node.right)
                else:
                    res += "\t"
            res += "\n"
            stack = another_stack
        return res
        


def generateTreesFromList(lst):
    if not lst:
        return [None]
    else:
        trees = []
        for i,v in enumerate(lst):
            left_trees = generateTreesFromList(lst[0:i])
            right_trees = generateTreesFromList(lst[i+1:])
            for left in left_trees:
                for right in right_trees:
                    root = TreeNode(lst[i])
                    root.left = left
                    root.right = right
                    trees.append(root)
        return trees

class Solution1:
    # @return a list of tree node
    def generateTrees(self, n):
        return generateTreesFromList(range(1,n+1))


def generateTreesFromRange(p,r):
    if p > r: return [None]
    
    trees = []
    for i in range(p,r+1):
        left_trees = generateTreesFromRange(p,i-1)
        right_trees = generateTreesFromRange(i+1,r)
        for left in left_trees:
            for right in right_trees:
                root = TreeNode(i)
                root.left = left
                root.right = right
                trees.append(root)
    return trees

class Solution:
    def generateTrees(self, n):
        return generateTreesFromRange(1,n)

sol = Solution()
print len(sol.generateTrees(3))
for tree in sol.generateTrees(3):
    print tree
    print
    print
