/**
 * struct TreeNode {
 *  int val;
 *  struct TreeNode *left;
 *  struct TreeNode *right;
 *  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * };
 */
#include <vector>
class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param proot TreeNode类
     * @param k int整型
     * @return int整型
     */

    int KthNode(TreeNode *proot, int k)
    {
        if (!proot)
            return -1;
        if (k < 1)
            return -1;
        vector<int> result;   // 存储遍历结果
        stack<TreeNode *> st; // 显式栈（不是vector）
        TreeNode *curr = proot;
        while (curr != nullptr || !st.empty())
        {
            // 1. 将当前节点及其所有左子节点入栈
            while (curr != nullptr)
            {
                st.push(curr);
                curr = curr->left;
            }
            // 2. 弹出栈顶节点并访问
            curr = st.top();
            st.pop();
            result.push_back(curr->val);
            // 3. 转向右子树
            curr = curr->right;
        }
        if (k > result.size())
            return -1;
        return result[k - 1];
    }
};