/**
 * struct ListNode {
 *  int val;
 *  struct ListNode *next;
 *  ListNode(int x) : val(x), next(nullptr) {}
 * };
 */
class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param pHead1 ListNode类
     * @param pHead2 ListNode类
     * @return ListNode类
     */
    ListNode *Merge(ListNode *pHead1, ListNode *pHead2)
    {
        // write code here
        if (pHead1 == nullptr)
            return pHead2;
        if (pHead2 == nullptr)
            return pHead1;

        // 归并排序
        auto head = new ListNode(-1);
        ListNode *cur = head;
        while (pHead1 != nullptr && pHead2 != nullptr)
        {
            if (pHead1->val <= pHead2->val)
            {
                cur->next = pHead1;
                cur = cur->next;
                pHead1 = pHead1->next;
            }
            else
            {
                cur->next = pHead2;
                cur = cur->next;
                pHead2 = pHead2->next;
            }
        }
        if (pHead1 != nullptr)
            cur->next = pHead1;

        if (pHead2 != nullptr)
            cur->next = pHead2;

        return head->next;
    }
};