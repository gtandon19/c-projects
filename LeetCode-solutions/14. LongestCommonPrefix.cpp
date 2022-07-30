/**
 * @file LongestCommonPrefix.cpp
 * @author geitanksha@gmail.com
 * @brief 14. Longest Common Prefix
 * @version 0.1
 * @date 2022-07-19
 *
 * @copyright Copyright (c) 2022 // LeetCode
 *
 */

class LongestCommonPrefix {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int shortestword = 250;
        string commpref = "";
        for (int i = 0; i < strs.size(); i++) {
            if (strs[i].length() < shortestword)
                shortestword = strs[i].length();
        }
        // i is the character, j is the word in list
        for (int i = 0; i < shortestword; i++) {
            char ch = strs[0].at(i);
            // cout << "i = " << i << " and ch = " << ch << endl;
            bool flag = true;
            for (int j = 1; j < strs.size(); j++) {
                if (ch != strs[j].at(i)) {
                    flag = false;
                    break;
                }
            }
            if (flag)
                commpref += ch;
            else
                break;
        }
        return commpref;
    }
};