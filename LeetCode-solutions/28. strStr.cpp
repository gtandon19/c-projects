/**
 * @file strStr.cpp
 * @author your name (you@domain.com)
 * @brief 28. Implement strStr()
 * @version 0.1
 * @date 2022-07-19
 *
 * @copyright Copyright (c) 2022 // LeetCode
 *
 */

class strStr {
public:
    int strStr(string haystack, string needle) {
        if (needle.length() > haystack.length())
            return -1;
        if (needle.length() == 0)
            return 0;
        for (int i = 0; i < haystack.length(); i++) {
            if (i + needle.length() == haystack.length() + 1)
                return -1;
            if (needle == haystack.substr(i, needle.length()))
                return i;
        }
        return -1;
    }
};