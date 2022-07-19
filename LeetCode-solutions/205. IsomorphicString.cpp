/**
 * @file IsomorphicString.cpp
 * @author geitanksha@gmail.com
 * @brief 205. Isomorphic Strings
 * @version 0.1
 * @date 2022-07-18
 * 
 * @copyright Copyright (c) 2022 // LeetCode
 * 
 */

class IsomorphicString
{
public:
    bool isIsomorphic(string s, string t)
    {
        vector<char> firstvec, secvec;
        for (int i = 0; i < s.length(); i++)
        {
            int j = 0;
            // bool flag = false;
            // traverse through vectors
            for (j = 0; j < firstvec.size(); j++)
            {
                if (s.at(i) == firstvec.at(j))
                {
                    if (t.at(i) != secvec.at(j))
                        return false;
                    break;
                }
                if (t.at(i) == secvec.at(j))
                {
                    if (s.at(i) != firstvec.at(j))
                        return false;
                    break;
                }
            }
            if (j == firstvec.size())
            {
                firstvec.push_back(s.at(i));
                secvec.push_back(t.at(i));
            }
        }
        return true;
    }
};