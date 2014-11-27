import collections

alphabets = ['a',
             'b',
             'c',
             'd',
             'e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']

def makeGraph(d):
    def connectedIter(s):
        s_list = list(s)
        for i in xrange(0, len(s_list)):
            for c in alphabets:
                if c != s[i]:
                    s_list[i] = c;
                    tmp_s = ''.join(s_list)
                    if tmp_s in d:
                        yield tmp_s
                    s_list[i] = s[i]
    return connectedIter

def bfs(start, end, dis, visited, g):
    q = collections.deque()
    q.append(start)
    dis[start] = 1
    visited.add(start)
    while q:
        u = q.popleft()
        dis_u = dis[u]
        for v in g(u):
            if v not in visited:
                if v == end:
                    return dis_u + 1
                q.append(v)
                visited.add(v)
                dis[v] = dis_u + 1
    return 0


class Solution:
    # @param start, a string
    # @param end, a string
    # @param dict, a set of string
    # @return an integer
    def ladderLength(self, start, end, d):
        visited = set()
        dis = dict()
        d.add(end)
        d.add(start)
        return bfs(start, end, dis, visited, makeGraph(d))
