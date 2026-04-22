class Solution
{
public:
    /*
    核心思想：
    只从“序列起点”开始扩展，避免重复扫描。
    步骤:
        所有元素放入 unordered_set
            遍历每个数 x：
            如果 x-1 不存在 → 说明是序列起点
            从 x 开始一直找 x+1, x+2...
        维护最长长度
    */
    int longestConsecutive(vector<int> &nums)
    {
        if (nums.empty())
            return 0;
        unordered_set<int> s(nums.begin(), nums.end());
        int count = 0;
        // 遍历集合防止超时
        for (int x : s)
        {
            if (s.find(x - 1) != s.end())
                continue;
            // x是开头
            int cur = x;
            int len = 1;
            while (s.find(cur + 1) != s.end())
            {
                ++cur;
                ++len;
            }
            count = max(count, len);
        }
        return count;
    }
};