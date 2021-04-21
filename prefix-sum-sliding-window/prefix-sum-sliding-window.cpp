#include <iostream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// Source: https://practice.geeksforgeeks.org/problems/equilibrium-point-1587115620/1#
// Function to find equilibrium point in the array.
// a: input array
// n: size of array
int equilibriumPoint( long long a[], int n )
{

    // Base case.
    if( n == 1 )
        return 1;

    // Calculate the sum of all elements of a.
    long long sum = 0;
    for( auto i = 0; i < n; ++i )
    {
        sum += a[ i ];
    }

    // sum - equilbrium point == cumsum[equilbrium point - 1]
    int eq = -1;
    long long leftSum = a[ 0 ];
    bool found = false;
    for( auto i = 1; i < ( n - 1 ); ++i )
    {
        if( ( sum - ( leftSum + a[ i ] ) ) == leftSum )
        {
            eq = i + 1;
            found = true;
            break;
        }
        leftSum += a[ i ];
    }

    return found ? eq : -1;
}

// Source: https://practice.geeksforgeeks.org/problems/subarray-with-0-sum-1587115621/1#
//Complete this function
//Function to check whether there is a subarray present with 0-sum or not.
bool subArrayExists( int arr[], int n )
{
    // Create a set which holds the unique elements of the cumulative sum.
    unordered_set<int> unique;

    // The subarray exists if the same element was found in unique more than once, or if any of the elements are 0.
    bool exists = false;
    long long sum = 0;
    for( auto i = 0; i < n; ++i )
    {
        sum += arr[ i ];
        if( arr[ i ] == 0 || unique.find( sum ) != unique.end() || sum == 0 )
        {
            exists = true;
            break;
        }

        unique.insert( sum );
    }

    return exists;
}

// Source: https://practice.geeksforgeeks.org/problems/longest-sub-array-with-sum-k0809/1
int lenOfLongSubarr( int A[], int N, int K )
{
    // unordered_map<cumsum, indx>
    unordered_map<long long, int> sumMap;
    int maxLen = 0;
    long long sum = 0;
    for( auto i = 0; i < N; ++i )
    {
        sum += A[ i ];

        // Update maxLen if sum == K
        if( sum == K )
        {
            maxLen = max( i + 1, maxLen );
        }

        // Update the map with the current cumsum.
        if( sumMap.find( sum ) == sumMap.end() )
        {
            sumMap[ sum ] = i;
        }

        // Update maxLen if there is a maximum subrange including the current element
        if( sumMap.find( sum - K ) != sumMap.end() )
        {
            maxLen = max( i - sumMap[ sum - K ], maxLen );
        }
    }

    return maxLen;
}

// Source: https://practice.geeksforgeeks.org/problems/longest-subarray-with-sum-divisible-by-k1259/1
int longSubarrWthSumDivByK( int arr[], int n, int k )
{
    // unordered_map<cumsum, indx>
    unordered_map<long long, int> sumMap;
    int maxLen = 0;
    long long sum = 0;
    for( auto i = 0; i < n; ++i )
    {
        sum += arr[ i ];

        // sum is divisible by K if this holds
        const int modK = ( ( sum % k ) + k ) % k;

        // Update maxLen if sum is divisible by k
        if( modK == 0 )
        {
            maxLen = max( i + 1, maxLen );
        }

        // Update the map with the current cumsum.
        if( sumMap.find( modK ) == sumMap.end() )
        {
            sumMap[ modK ] = i;
        }

        // Update maxLen if there is a maximum subrange divisible by K including the current element
        auto pModK = sumMap.find( modK );
        if( pModK != sumMap.end() )
        {
            maxLen = max( i - pModK->second, maxLen );
        }
    }

    return maxLen;
}

int main( int argc, char* argv[] )
{
    return 0;
}