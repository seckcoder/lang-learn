

class Node:
    def __init__(self, c):
        self.c = c
        self.nodes = {}

    def insert(self, s):
        if not s:
            return
        elif self.nodes.has_key(s[0]):
            self.nodes[s[0]].insert(s[1:])
        else:
            self.nodes[s[0]] = Node(s[0])
            self.nodes[s[0]].insert(s[1:])
    
    def lookup(self, s):
        if not s: return True
        if self.nodes.has_key(s[0]):
            return self.nodes[s[0]].lookup(s[1:])
        else:
            return False

class Trie:
    def __init__(self):
        self.root = Node('')

    def insert(self, s):
        self.root.insert(s)

    def lookup(self, s):
        return self.root.lookup(s)

trie = Trie()

trie.insert("abc")
print trie.lookup("abc")
print trie.lookup("abd")
trie.insert("def")
print trie.lookup("def")
