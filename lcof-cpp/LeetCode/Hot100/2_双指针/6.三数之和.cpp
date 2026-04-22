class Solution
{
public:
    /*
    思路:
    排序 + 双指针
    1. 先排序
    2. 固定一个数 num1, 双指针 left right
        可以减枝:看具体情况
            num1 > 0 break
            num1 + nums[i+1] + nums[i+2] > 0 break
            num1 + nums[n-2] + nums[n-1] < 0 continue
        target = num1 + nums[left] + nums[right]
        target < 0 left++
        target > 0 right--
        target == 0 => 可以减枝 存入结果
    */
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        if (nums.size() < 3)
            return {};
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());
        // 先减枝
        if (nums[nums.size() - 1] < 0 || nums[0] > 0)
            return {};
        for (int i = 0; i < nums.size() - 2; ++i)
        {
            int num1 = nums[i];
            // 去重
            if (i > 0 && num1 == nums[i - 1])
                continue;
            // 如果连续三个已经大于0 说明后面的肯定更大 break
            if (num1 + nums[i + 1] + nums[i + 2] > 0)
                break;
            // 如果当前数加上最大的数还是小于0
            if (num1 + nums[nums.size() - 2] + nums[nums.size() - 1] < 0)
                continue;
            // 双指针
            int left = i + 1, right = nums.size() - 1;
            while (left < right)
            {
                long target = num1 + nums[left] + nums[right];
                if (target < 0)
                {
                    ++left;
                }
                else if (target > 0)
                {
                    --right;
                }
                else
                {
                    ans.emplace_back(vector<int>{num1, nums[left], nums[right]});
                    while (left < right && nums[left] == nums[left + 1])
                        ++left;
                    while (left < right && nums[right] == nums[right - 1])
                        --right;
                    ++left;
                    --right;
                }
            }
        }
        return ans;
    }
};