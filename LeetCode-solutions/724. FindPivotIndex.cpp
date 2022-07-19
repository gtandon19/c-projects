/**
 * @file FindPivotIndex.cpp
 * @author geitanksha@gmail.com
 * @brief 724. Find Pivot Index
 * @version 0.1
 * @date 2022-07-18
 * 
 * @copyright Copyright (c) 2022 // LeetCode
 * 
 */

class FindPivotIndex
{
public:
    int pivotIndex(vector<int> &nums)
    {
        int lsum = 0, rsum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            rsum += nums[i];
        }

        for (int i = 0; i < nums.size(); i++)
        {
            rsum -= nums[i];
            if (i != 0)
                lsum += nums[i - 1];

            if (lsum == rsum)
            {
                return i;
            }
        }
        return -1;
    }
};