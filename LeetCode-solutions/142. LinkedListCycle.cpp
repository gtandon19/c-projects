/**
 * @brief 142. Linked List Cycle II
 *
 */
 * Definition for singly-linked list.
 * struct ListNode
 {
     *int val;
     *ListNode *next;
     *ListNode(int x) : val(x), next(NULL){}
                                    *
 };
 * /

     class linkedlistcycle
 {
 public:
     ListNode *detectCycle(ListNode *head)
     {
         vector<ListNode *> visited;
         ListNode *curr = head;
         while (curr != NULL)
         {
             for (int i = 0; i < visited.size(); i++)
             {
                 if (curr == visited[i])
                 {
                     return curr;
                 }
             }
             visited.push_back(curr);
             curr = curr->next;
         }
         return NULL;
     }
 };