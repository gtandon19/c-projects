/**
 * @file RunningSum.cpp
 * @author geitanksha@gmail.com
 * @brief 1480. Running Sum of 1d Array
 * @version 0.1
 * @date 2022-07-18
 * 
 * @copyright Copyright (c) 2022 // LeetCode
 * 
 */

class RunningSum
{
public:
    vector<int> runningSum(vector<int> &nums)
    {

        vector<int> ans;
        if (!nums.size())
            return ans;
        ans.push_back(nums[0]);
        for (int i = 1; i < nums.size(); i++)
        {
            ans.push_back((ans[i - 1] + nums[i]));
        }
        return ans;
    }
};