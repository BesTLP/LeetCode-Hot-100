#include "iostream"
#include "cstdio"

struct ListNode 
{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};
class Solution 
{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
    {
        ListNode* PreviousNode = nullptr;
        ListNode* FirstNode = nullptr;
        int Temp = 0; // 进位

        while (l1 || l2 || Temp)
        {
            int x = l1 != nullptr? l1->val : 0;
            int y = l2 != nullptr? l2->val : 0;

            if (FirstNode == nullptr)
            {
                FirstNode = new ListNode();
                FirstNode->val = (x + y + Temp) % 10;
                PreviousNode = FirstNode;
            }
            else
            {
                ListNode* CurrentNode = new ListNode();
                CurrentNode->val = (x + y + Temp) % 10;
                PreviousNode->next = CurrentNode;
                PreviousNode = CurrentNode;
            }
            Temp = (x + y + Temp) / 10; // 获取到进位
            l1 = l1 != nullptr? l1->next : nullptr;
            l2 = l2 != nullptr? l2->next : nullptr;
        }

        return FirstNode;
    }
public:
};
