/**
 * @brief 21. Merge Two Sorted Lists // using Singly Linked List
 *
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class MergeTwoSortedLists
{
public:
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
    {
        ListNode *head;
        if (list1 == NULL)
            return list2;
        if (list2 == NULL)
            return list1;
        if (list1->val >= list2->val)
        {
            head = list2;
            list2 = list2->next;
        }
        else
        {
            head = list1;
            list1 = list1->next;
        }
        ListNode *newlist = head;
        while (list1 != NULL && list2 != NULL)
        {
            if (list1->val >= list2->val)
            {
                newlist->next = list2;
                list2 = list2->next;
            }
            else
            {
                newlist->next = list1;
                list1 = list1->next;
            }
            newlist = newlist->next;
        }
        while (list1 != NULL)
        {
            newlist->next = list1;
            newlist = newlist->next;
            list1 = list1->next;
        }
        while (list2 != NULL)
        {
            newlist->next = list2;
            newlist = newlist->next;
            list2 = list2->next;
        }
        return head;
    }
};