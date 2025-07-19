#include <unordered_map>
struct ListNode
{
    ListNode* next;
};
class Solution
{
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB)
    {
        std::unordered_map<ListNode*, bool> mp;
        while (headA)
        {
            mp[headA] = true;
            headA = headA->next;
        }

        while (headB)
        {
            if (mp.find(headB) != mp.end())
            {
                break;
            }
            else
            {
                headB = headB->next;
            }
        }

        return headB;
    }
};

#include <vector>
//Definition for singly-linked list.

class Solution
{
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB)
    {
        ListNode* tempA = headA;
        ListNode* tempB = headB;
        if (headA == nullptr && headB == nullptr)
        {
            return nullptr;
        }
        bool flagA = false;
        bool flagB = false;
        while (true)
        {
            if (headA == headB)
            {
                break;
            }
            if (headA)
                headA = headA->next;
            if (headB)
                headB = headB->next;

            if (!headA && !flagA)
            {
                headA = tempB;
                flagA = true;
            }
            if (!headB && !flagB)
            {
                headB = tempA;
                flagB = true;
            }
        }

        return headA;
    }
};