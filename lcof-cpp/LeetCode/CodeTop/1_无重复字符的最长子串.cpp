class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        std::unordered_map<char, int> map;
        int start = -1;
        int maximum = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            // 出现过 || 出现过不代表它还在当前窗口内
            if (map.find(s[i]) != map.end() && map[s[i]] > start)
            {
                start = map[s[i]]; // 找到了相同得字符 要压缩滑动窗口
                map[s[i]] = i;
            }
            else
            {
                map[s[i]] = i;
                if (i - start > maximum)
                    maximum = i - start;
            }
        }
        return maximum;
    }
};