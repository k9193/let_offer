class Solution
{
public:
    /*
    思路:双指针 右边挡板更高 就移动左边挡板 反之移动右边挡板
    1. 比较 h[l], h[r]
    2. 选较小一侧
    3. 用该侧 max 计算水
    4. 更新该侧 max
    5. 移动该指针
    */
    int trap(vector<int> &height)
    {
        int l = 0, r = height.size() - 1;
        int left_max = 0, right_max = 0;
        int ans = 0;

        while (l < r)
        {
            if (height[l] < height[r])
            {
                if (left_max < height[l])
                    left_max = height[l];
                else
                    ans += left_max - height[l];
                ++l;
            }
            else
            {
                if (right_max < height[r])
                    right_max = height[r];
                else
                    ans += right_max - height[r];
                --r;
            }
        }
        return ans;
    }
};