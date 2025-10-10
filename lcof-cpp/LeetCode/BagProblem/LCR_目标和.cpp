class Solution
{
public:
    // sum已知 neg已知 所以 (sum-neg)-neg == target
    // 所以 neg = (sum-target)/2 不能整除就不行 不过本题肯定可以
    int findTargetSumWays(vector<int> &nums, int target)
    {
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        if ((sum - target) % 2 != 0 || (sum - target) < 0)
            return 0;
        int neg = (sum - target) / 2;
        int n = nums.size();
        // 剩下就是背包 在[0~j]区间选择 看看是否能到达neg
        vector<vector<int>> dp(n + 1, vector<int>(neg + 1));
        dp[0][0] = 1;
        // 如果 j<num，则不能选 num，此时有 dp[i][j]=dp[i−1][j] 解析:num大于目标值 只能把下面的复制过来
        // j≥num 则如果不选 num，方案数是 dp[i−1][j] 如果选 num，方案数是 dp[i−1][j−num]
        for (int i = 1; i < n + 1; ++i)
        {
            int num = nums[i - 1]; // 获得当前可以选择的数
            for (int j = 0; j < neg + 1; ++j)
            {
                dp[i][j] = dp[i - 1][j]; // 先把不选当前数可以到达的容量记录下来
                if (j >= num)
                    dp[i][j] += dp[i - 1][j - num]; // 找有什么能和 num凑出j的序列
            }
        }
        return dp[n][neg];
    }
};