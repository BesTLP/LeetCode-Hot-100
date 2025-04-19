#include <vector>
#include <iostream>

// Definition for singly-linked list.
struct ListNode 
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution 
{
public:
    bool isPalindrome(ListNode* head) 
    {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        if (fast) 
        {
            slow = slow->next; // 如果是奇数个节点，跳过中间节点
        }
        // 此时slow的指针位置就是要反转链表的首节点
        ListNode* ptr1 = reverseList(slow);
        ListNode* ptr2 = head;
        while (ptr1 && ptr2)
        {
            if (ptr1->val != ptr2->val)
            {
                return false;
            }
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        return true;
    }
    ListNode* reverseList(ListNode* head)
    {
        ListNode* pre = nullptr;
        ListNode* cur = head;
        while (cur)
        {
            ListNode* next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return pre;
    }
};

//int main()
//{
//    Solution solution;
//    ListNode* head = new ListNode(1);
//    head->next = new ListNode(2);
//    head->next->next = new ListNode(2);
//    head->next->next->next = new ListNode(1);
//    solution.isPalindrome(head);
//}