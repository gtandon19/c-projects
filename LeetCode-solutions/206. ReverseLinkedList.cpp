/**
 * @brief 206. Reverse Linked List
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
     class ReverseLinkedList
 {
 public:
     ListNode *reverseList(ListNode *head)
     {
         if (head == NULL || head->next == NULL)
             return head;
         if (head->next->next == NULL)
         {
             ListNode *tmp = head;
             head = head->next;
             head->next = tmp;
             tmp->next = NULL;
             return head;
         }
         ListNode *curr = head->next, *prev = head, *nex = curr->next;
         head->next = NULL;
         while (nex != NULL)
         {
             curr->next = prev;
             prev = curr;
             curr = nex;
             nex = nex->next;
         }
         curr->next = prev;
         head = curr;
         return head;
     }
 };