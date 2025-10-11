class Solution
{
public:
    long long maximumTotalDamage(vector<int> &power)
    {
        int n = power.size();
        std::sort(power.begin(), power.end());
        vector<vector<long long>> dp(n, vector<long long>(2));
        dp[0][1] = power[0];
        for (int i = 1; i < n; ++i)
        {
            if (power[i] == power[i - 1])
            {
                // 因为伤害一样,上一个不选 这个也不能选， 上一个选了 这个肯定也要选
                dp[i][0] = dp[i - 1][0];
                dp[i][1] = power[i] + dp[i - 1][1];
                continue;
            }
            // 伤害不一样的情况 首先不选
            dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1]);
            dp[i][1] = power[i];
            // 选
            long long target = power[i] - 3; // 要找伤害<=3的时候的dp数组 找那个时候的最大值
            int backtraceIndex = i;
            // 回溯 从1开始 只能到0
            while (backtraceIndex > 0 && power[backtraceIndex] > target)
            {
                --backtraceIndex;
            }
            if (power[backtraceIndex] <= target)
                dp[i][1] += std::max(dp[backtraceIndex][0], dp[backtraceIndex][1]);
        }
        return std::max(dp[n - 1][0], dp[n - 1][1]);
    }
};

class Solution
{
public:
    long long maximumTotalDamage(vector<int> &power)
    {
        vector<long long> dp(4, 0);
        ranges::sort(power);
        dp[3] = power[0];
        for (int i = 1; i < power.size(); ++i)
        {
            if (power[i] == power[i - 1])
            {
                dp[3] += power[i];
            }
            else if (power[i] == power[i - 1] + 1)
            {
                // [x,y,z,0] ->[x,y,z,0,1]-> [max(x,y),z,0,x+power[i]] 需要保证是合法状态 xyz至少差1
                dp[0] = std::max(dp[0], dp[1]);
                dp[1] = dp[2];
                dp[2] = dp[3];
                dp[3] = dp[0] + power[i];
            }
            else if (power[i] == power[i - 1] + 2)
            {
                // [x,y,z,0]  ->[x,y,z,0,2]-> [max(x,y,z),0, 0, x+power[i]]
                dp[0] = max({dp[0], dp[1], dp[2]});
                dp[1] = dp[3];
                dp[2] = dp[3];
                dp[3] = dp[0] + power[i];
            }
            else
            {
                // [x,y,z,0]  ->[x,y,z,0,3]-> [max(x,y,z,0),0, 0, x+power[i]]
                dp[0] = max({dp[0], dp[1], dp[2], dp[3]});
                dp[1] = dp[3];
                dp[2] = dp[3];
                dp[3] = dp[0] + power[i];
            }
        }
        return ranges::max(dp);
    }
};