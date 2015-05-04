# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None


# Key Idea: Cut the list into two parts at the new head after rotation.

class Solution:
    # @param head, a ListNode
    # @param k, an integer
    # @return a ListNode
    def length(self, head):
        len = 0
        while head:
            len += 1
            head = head.next
        return len
            
    def walk(self, sentinel, steps):
        # assert we won't walk to the end
        for i in xrange(0,steps):
            # assert sentinel will never be None
            sentinel = sentinel.next
        
        return sentinel
            
    def tail(self, head):
        # assert head != None
        while head.next:
            head = head.next
        return head
    
    def rotateRight(self, head, k):
        num_nodes = self.length(head)
        if num_nodes == 0: return head
        k = k % num_nodes
        if k == 0: return head
        
        sentinel = ListNode(0)
        sentinel.next = head
        # num_nodes >= 2, 1 <= k < num_nodes
        prev = self.walk(sentinel, num_nodes-k)
        new_head = prev.next
        prev.next = None
        tail = self.tail(new_head)
        
        tail.next = sentinel.next
        
        return new_head
