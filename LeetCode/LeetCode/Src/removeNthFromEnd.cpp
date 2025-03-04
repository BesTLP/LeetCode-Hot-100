#include "iostream"
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
    ListNode* removeNthFromEnd(ListNode* head, int n) 
    {
        if ((!head->next && n >= 1) || !head )
        {
            // 如果只有一个节点, 或者根本没有节点
            head = nullptr;
            return head;    
        }

        ListNode* NextN = head; // 快指针
        ListNode* Current = head; // 慢指针
        for (int i = 1; i <= n; i++)
            NextN = NextN->next;

        if (NextN == nullptr)
        {
            Current = head;
            if(head != nullptr)
                head = head->next;

            delete Current;

            return head;
        }

        while (NextN->next)
        {
            NextN = NextN->next;
            Current = Current->next;
        }

        ListNode* ToDelete = Current->next;
        Current->next = Current->next->next;
        delete ToDelete;

        return head;
    }
};