class Solution
{
public:
    /*
    思路:双指针
    容器面积由两部分决定：
        宽度：r−l
        高度：min(height[l],height[r])
        面积受限于短板（min）
        如果移动长板 → 宽度变小，高度不会变大 → 一定变差
        如果移动短板 → 宽度变小，高度可能变大 → 可能变好
    */
    int maxArea(vector<int> &height)
    {
        int l = 0, r = height.size() - 1;
        int ans = 0;
        while (l < r)
        {
            int h = std::min(height[l], height[r]);
            ans = max(ans, (r - l) * h);
            if (height[l] < height[r])
                ++l;
            else
                --r;
        }
        return ans;
    }
};