/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};*/
#include <queue>
#include <vector>
class Solution
{
public:
    vector<int> PrintFromTopToBottom(TreeNode *root)
    {
        vector<int> res;
        if (root == nullptr)
            return res;
        queue<TreeNode *> q;
        q.push(root);
        TreeNode *cur;
        while (!q.empty())
        {
            int n = q.size();
            for (int i = 0; i < n; ++i)
            {
                cur = q.front();
                q.pop();
                res.emplace_back(cur->val);
                if (cur->left)
                    q.push(cur->left);
                if (cur->right)
                    q.push(cur->right);
            }
        }
        return res;
    }
};
