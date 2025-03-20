#include <iostream>
//Definition for singly-linked list.
 struct ListNode 
 {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(nullptr) {}
 };

#include <iostream>
 class Solution
 {
 public:
     ListNode* detectCycle(ListNode* head)
     {
         if (head == nullptr) return nullptr;
         if (head->next == nullptr) return nullptr;

         ListNode* slow = head;
         ListNode* fast = head;
         while (slow && fast && fast->next)
         {
             slow = slow->next;
             fast = fast->next->next;
             if (slow == fast) break;
         }

         if (!slow || !fast)
         {
             return nullptr;
         }

         fast = head;
         while (fast != slow)
         {
             if (fast) fast = fast->next;
             if (slow) slow = slow->next;
         }
         return fast;
     }
 };
//
//int main()
//{
//    ListNode* head = new ListNode(3);
//    head->next = new ListNode(2);
//    head->next->next = new ListNode(0);
//    head->next->next->next = new ListNode(-4);
//    head->next->next->next->next = head->next;
//    Solution solution;
//    solution.detectCycle(head);
//}