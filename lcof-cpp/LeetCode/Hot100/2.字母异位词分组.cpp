class Solution
{
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        vector<vector<string>> ans;
        unordered_map<string, vector<string>> map;
        for (auto &str : strs)
        {
            string key = str;
            sort(key.begin(), key.end());
            map[key].emplace_back(str);
        }
        for (auto &pair : map)
        {
            ans.emplace_back(pair.second);
        }
        return ans;
    }
};