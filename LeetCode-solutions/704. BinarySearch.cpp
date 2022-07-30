/**
 * @file BinarySearch.cpp
 * @author geitanksha@gmail.com
 * @brief 704. Binary Search
 * @version 0.1
 * @date 2022-07-29
 *
 * @copyright Copyright (c) 2022 // LeetCode
 *
 */

class BinarySearch
{
public:
    int search(vector<int>& nums, int target) {
        if (nums.size() == 0)
            return -1;
        if (nums.size() == 1) {
            if (nums[0] == target)
                return 0;
            return -1;
        }
        int l = 0, m = nums.size() / 2, r = nums.size() - 1;
        while (l <= r) {
            if (nums[m] == target)
                return m;
            if (target < nums[m])
                r = m - 1;
            else
                l = m + 1;
            m = (l + r) / 2;
        }
        return -1;
    }
};