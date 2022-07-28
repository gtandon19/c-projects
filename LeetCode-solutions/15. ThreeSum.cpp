/**
 * @file ThreeSum.cpp
 * @author geitanksha@gmail.com
 * @brief 15. 3Sum
 * @version 0.1
 * @date 2022-07-19
 *
 * @copyright Copyright (c) 2022 // LeetCode
 *
 */

class ThreeSum
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        vector<vector<int>> ans;
        // sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = 0; j < nums.size(); j++)
            {
                for (int k = 0; k < nums.size(); k++)
                {
                    if (i == j || i == k || j == k)
                        break;
                    if (nums[i] + nums[j] + nums[k] == 0)
                    {
                        vector<int> vect{nums[i], nums[j], nums[k]};
                        for (int a = 0; a < 3; a++)
                        {
                            for (int b = 0; b < 3; b++)
                            {
                                if (vect[a] > vect[b])
                                {
                                    int temp = vect[a];
                                    vect[a] = vect[b];
                                    vect[b] = temp;
                                }
                            }
                        }
                        bool flag = false;
                        for (int a = 0; a < ans.size(); a++)
                        {
                            if (ans[a][0] == vect[0] && ans[a][1] == vect[1] && ans[a][2] == vect[2])
                            {
                                flag = true;
                                break;
                            }
                        }
                        if (!flag)
                            ans.push_back(vect);
                    }
                }
            }
        }

        return ans;
    }
};