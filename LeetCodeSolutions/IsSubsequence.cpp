/**
 * @file IsSubsequence.cpp
 * @author geitanksha@gmail.com
 * @brief 392. Is Subsequence
 * @version 0.1
 * @date 2022-07-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

class Solution
{
public:
    bool isSubsequence(string s, string t)
    {
        string ans = "";
        if (s.length() > t.length())
            return false;
        int i = 0, j = 0;
        for (; i < s.length(); i++)
        {
            for (; j < t.length(); j++)
            {
                if (s.at(i) == t.at(j))
                {
                    ans += s.at(i);
                    j++;
                    break;
                }
            }
        }
        if (ans == s)
            return true;
        return false;
    }
};