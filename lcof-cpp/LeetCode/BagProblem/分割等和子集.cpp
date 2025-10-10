class Solution
{
public:
    bool canPartition(vector<int> &nums)
    {
        if (nums.size() < 2)
            return false;
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        if ((sum % 2) == 1)
            return false;
        int target = sum >> 1;
        int n = nums.size();
        vector<vector<int>> dp(n + 1, vector<int>(target + 1));
        dp[0][0] = 1;
        for (int i = 1; i < n + 1; ++i)
        {
            int selectVal = nums[i - 1]; // 获得当前val
            for (int j = 0; j < target + 1; ++j)
            {
                if (j >= selectVal)
                    dp[i][j] = dp[i - 1][j] | dp[i - 1][j - selectVal];
                else
                    dp[i][j] = dp[i - 1][j];
            }
        }
        return dp.back().back() != 0;
    }
};