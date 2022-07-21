/**
 * @file MergeSortedVectors.cpp
 * @author geitanksha@gmail.com
 * @brief 88. Merge Sorted Array
 * @version 0.1
 * @date 2022-07-19
 *
 * @copyright Copyright (c) 2022 // LeetCode
 *
 */

class MergeSortedVectors
{
public:
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
    {
        int i = m + n - 1;
        int a = m - 1, b = n - 1;
        if (m == 0)
        {
            for (int x = 0; x < n; x++)
                nums1[x] = nums2[x];
        }
        while (i >= 0 && a >= 0 && b >= 0)
        {

            if (nums1[a] >= nums2[b])
            {
                nums1[i] = nums1[a];
                a--;
            }
            else
            {
                nums1[i] = nums2[b];
                b--;
            }
            i--;
        }
        while (b >= 0)
            nums1[i--] = nums2[b--];
    }
};