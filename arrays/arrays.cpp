#include <vector>

// Source: https://www.geeksforgeeks.org/problems/subarray-with-given-sum-1587115621/1
//Function to find a continuous sub-array which adds up to a given number.
std::vector<int> subarraySum(std::vector<int>arr, int n, long long s)
{
    /*
    * 2 pointers left and right both inited to 0
    * sum = 0
    * while right < n
    * {
    *   while right < n AND sum + arr[right] <= s
    *       sum += arr[right++]
    *   if sum == s
    *       return {left+1, right+1}
    *   else if right < n
    *       while sum >= s AND left < right
    *           sum -= arr[left++]
    * }
    * return {-1, -1}
    */
    int sum = 0, left = 0, right = 0;
    while( right < n )
    {
        // Return if sum has been reached
        if (sum == s)
            return std::vector<int>{left + 1, right + 1};

        // Advance right pointer while sum <= s
        while ( right < n && ( sum + arr[right] <= s ) )
            sum += arr[right++];

        // Advance left pointer until sum falls just below s
        if ( right < n && sum != s )
        {
            sum += arr[right]; // Include the right element
            while (sum > s && left < right)
                sum -= arr[left++];
        }
        else
        {
            --right;    // Decrement right pointer since we've hit the sum
        }
    }
    return { -1, -1 };
}

int main()
{
    std::vector<int> data{ 1, 2, 3, 7, 5 }, data2{ 1,2,3,4,5,6,7,8,9,10 };
    auto result1 = subarraySum(data, data.size(), 12);
    auto result2 = subarraySum(data2, data2.size(), 15);
    return 0;
}