/**
 * @file MaxProfit.cpp
 * @author geitanksha@gmail.com
 * @brief 121. Best Time to Buy and Sell Stock
 * @version 0.1
 * @date 2022-07-20
 *
 * @copyright Copyright (c) 2022
 *
 */

class MaxProfit
{
public:
    int maxProfit(vector<int> &prices)
    {
        int minval = prices[0], maxprof = 0;
        for (int i = 0; i < prices.size(); i++)
        {
            // first find the smallest value in the array as we proceed
            if (prices[i] < minval)
                minval = prices[i];
            // once we have a working minimum, check if the max profit can be obtained by subtracting minimum value from the current value
            if ((prices[i] - minval) > maxprof)
                maxprof = prices[i] - minval;
        }
        return maxprof;
    }
};