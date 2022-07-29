/**
 * @brief 876. Middle of the Linked List
 *
 */
 * Definition for singly-linked list.
 * struct ListNode
 {
     *int val;
     *ListNode *next;
     *ListNode() : val(0), next(nullptr){} * ListNode(int x) : val(x), next(nullptr){} * ListNode(int x, ListNode *next) : val(x), next(next){}
                                                                                                                                       *
 };
 * /
     class MiddleNode
 {
 public:
     ListNode *middleNode(ListNode *head)
     {
         ListNode *curr = head;
         int num = 0;
         while (curr != NULL)
         {
             num++;
             curr = curr->next;
         }
         num /= 2;
         num++;
         curr = head;
         for (int i = 1; i < num; i++)
         {
             curr = curr->next;
         }
         return curr;
     }
 };