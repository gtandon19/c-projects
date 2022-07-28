/**
 * @file RomanToInt.cpp
 * @author your name (you@domain.com)
 * @brief 13. Roman to Integer
 * @version 0.1
 * @date 2022-07-19
 *
 * @copyright Copyright (c) 2022 // LeetCode
 *
 */

using namespace std;
class RomanToInt
{
public:
    int romanToInt(string s)
    {
        int sum = 0;
        for (int i = 0; i < s.length(); i++)
        {
            switch (s.at(i))
            {
            case 'M':
                sum += 1000;
                break;
            case 'D':
                sum += 500;
                break;
            case 'C':
                if ((i != s.length() - 1) && (s.at(i + 1) == 'D'))
                {
                    i++; // to increment to other letter after combination
                    sum += 400;
                }
                else if ((i != s.length() - 1) && (s.at(i + 1) == 'M'))
                {
                    i++;
                    sum += 900;
                }
                else
                    sum += 100;
                break;
            case 'L':
                sum += 50;
                break;
            case 'X':
                if ((i != s.length() - 1) && (s.at(i + 1) == 'L'))
                {
                    i++; // to increment to other letter after combination
                    sum += 40;
                }
                else if ((i != s.length() - 1) && (s.at(i + 1) == 'C'))
                {
                    i++;
                    sum += 90;
                }
                else
                    sum += 10;
                break;
            case 'V':
                sum += 5;
                break;
            case 'I':
                if ((i != s.length() - 1) && (s.at(i + 1) == 'V'))
                {
                    i++; // to increment to other letter after combination
                    sum += 4;
                }
                else if ((i != s.length() - 1) && (s.at(i + 1) == 'X'))
                {
                    i++;
                    sum += 9;
                }
                else
                    sum += 1;
                break;
            }
        }
        return sum;
    }
};