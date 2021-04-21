#include <vector>
#include <iostream>
#include <string>

using namespace std;

/* Iterative Function to calculate (x^y)%p in O(log y) */
long long power( int N, int R )
{
    // Taken from: https://www.geeksforgeeks.org/modular-exponentiation-power-in-modular-arithmetic/
    // Video walkthrough: https://www.youtube.com/watch?v=VJ7mkRu3sNc
    long long x = N, y = R; // Convert to long long to avoid truncation
    long long res = 1;     // Initialize result
    static const long long p = 1000000007; // Modulo

    x = x % p; // Update x if it is more than or equal to p

    if( x == 0 ) return 0; // In case x is divisible by p;

    while( y > 0 )
    {
        // If y is odd, multiply N with result
        if( y & 1 )
            res = ( res * x ) % p;

        // y must be even now
        y = y >> 1; // y = y/2
        x = ( x * x ) % p;
    }
    return res;
}

// Return last digit of the n'th Fibonacci number.
// Source: https://practice.geeksforgeeks.org/problems/the-nth-fibonnaci3150/1
// Solution based of space optimized method here: https://www.geeksforgeeks.org/program-for-nth-fibonacci-number/
long long fibbonaci( int n )
{
    long long sum = 0;  // sum tracks fib(n)
    long long t1 = 0;   // t1 tracks fib(n-2)
    long long t2 = 1;   // t2 tracks fib(n-1)
    for( int i = 2; i <= n; i++ )
    {
        sum = ( t1 + t2 ) % 10; // Modulo 10 here and below since we're tracking the last digit only
        t1 = t2 % 10;
        t2 = sum % 10;
    }

    return sum;
}
int fib( int N )
{

    if( N == 0 )
    {
        return N;
    }
    if( N == 1 )
    {
        return 1;
    }
    long long s = fibbonaci( N );

    return s;
    //code here
}

int kthElement( int arr1[], int arr2[], int n, int m, int k )
{
    int start = 0;
    int end = n;
    int output;

    static constexpr bool debugPrints = true;    

    while( start <= end )
    {
        if( debugPrints )
        {
            cout << "\n\nstart = " << start << "; end = n = " << end << endl;
        }

        int mid = start + ( end - start ) / 2;
        int mid2 = k - mid;
        if( debugPrints )
        {
            cout << "mid = start + ( end - start ) / 2  = " << mid << endl << "mid2 = k - mid = " << mid2 << endl;
        }

        if( mid2 > m )
        {
            start = mid + 1;
            if( debugPrints )
            {
                cout << "mid2 > m: start = mid + 1 = " << start << endl;
            }
            continue;
        }

        if( mid2 < 0 )
        {
            end = mid - 1;
            if( debugPrints )
            {
                cout << "mid2 < 0: end = mid - 1 = " << end << endl;
            }
            continue;
        }

        int x1 = ( mid > 0 ) ? arr1[ mid - 1 ] : INT_MIN;
        int x2 = ( mid < n ) ? arr1[ mid ] : INT_MAX;
        int y1 = ( mid2 > 0 ) ? arr2[ mid2 - 1 ] : INT_MIN;
        int y2 = ( mid2 < n ) ? arr2[ mid2 ] : INT_MAX;
        if( debugPrints )
        {
            cout << "x1 = ( mid > 0 ) ? arr1[ mid - 1 ] = " << x1 << endl;
            cout << "x2 = ( mid < n ) ? arr1[ mid ] : INT_MAX = " << x2 << endl;
            cout << "y1 = ( mid2 > 0 ) ? arr2[ mid2 - 1 ] : INT_MIN = " << y1 << endl;
            cout << "y2 = ( mid2 < n ) ? arr2[ mid2 ] : INT_MAX = " << y2 << endl;
        }

        if( x1 <= y2 && y1 <= x2 )
        {
            // Found a position.
            output = max( x1, y1 );
            end = mid - 1;
            if( debugPrints )
            {
                cout << "x1 <= y2 && y1 <= x2: output = max( x1, y1 ) = " << output << "; end = mid - 1 = " << end << endl;
            }
        }
        else if( y1 > x2 )
        {
            // Shift right
            start = mid + 1;
            if( debugPrints )
            {
                cout << "y1 > x2: start = mid + 1 = " << start << endl;
            }
        }
        else
        {
            // Shift left
            end = mid - 1;
            if( debugPrints )
            {
                cout << "end = mid - 1 = " << end << endl;
            }
        }
    }

    return output;
}

// Source: https://practice.geeksforgeeks.org/problems/karatsuba-algorithm0135/1#
unsigned long long karatsubaAlgo( string A, string B )
{
    // Int aInt and bInt to 0
    unsigned long long aInt = 0, bInt = 0;

    // Get the lengths of A and B and the max.
    const auto aLen = A.length(), bLen = B.length(), cLen = max( aLen, bLen );

    // Traverse A and B backwards and compute the decimal representations of each.
    for( auto i = 0; i < cLen; ++i )
    {
        const unsigned long long multiplier = (1 << i);
        if( i < aLen )
        {
            aInt += multiplier * ( static_cast<int>( A[ aLen - i - 1 ] ) - 48 );
            //cout << "aInt = " << aInt << endl;
        }
        if( i < bLen )
        {
            bInt += multiplier * ( static_cast<int>( B[ bLen - i - 1 ] ) - 48 );
            //cout << "bInt = " << bInt << endl;
        }
    }

    return ( aInt * bInt );
}

// Source: https://www.geeksforgeeks.org/painters-partition-problem/
// function to calculate sum between two indices
// in array
int sum( int arr[], int from, int to )
{
    int total = 0;
    for( int i = from; i <= to; i++ )
        total += arr[ i ];
    return total;
}

// bottom up tabular dp
int findMax( int arr[], int n, int k )
{
    // initialize table
    //int dp[ k + 1 ][ n + 1 ] = { 0 };
    vector<int> dp( ( k + 1 ) * ( n + 1 ), 0 );
    const auto nSize = static_cast<size_t>( n );

    // Linear index given row and column.
    auto indx = [&]( const size_t r, const size_t c )
    {
        return r * ( nSize + 1 ) + c;
    };

    // base cases
    // k=1
    //int sum[ n + 1 ] = { 0 };
    vector<int> sum( n + 1, 0 );

    // sum from 1 to i elements of arr
    // Cumulative sum keeps track of accummulated time assuming 1 painter does all the work.
    cout << "sum = {0, ";
    for( size_t i = 1; i <= n; i++ )
    {
        sum[ i ] = sum[ i - 1 ] + arr[ i - 1 ];
        cout << sum[ i ] << ", ";
    }
    cout << "}\n";

    // dp[1] tracks if 1 painter does all the work, same as cumsum.
    for( size_t i = 1; i <= n; i++ )
        dp[ indx( 1, i ) ] = sum[ i ];

    // 2 to k partitions
    for( size_t i = 2; i <= k; i++ )
    { // 2 to n boards
        for( size_t j = 2; j <= n; j++ )
        {

            // track minimum
            int best = INT_MAX;

            // i-1 th separator before position arr[p=1..j]
            for( size_t p = 1; p <= j; p++ )
            {
                cout << "i: " << i << "; j: " << j << "; p: " << p << "; best = min( best, max( dp[ indx( i - 1, p ) ], sum[ j ] - sum[ p ] ) ) = "
                    << "min( " << best << ", max( " << dp[ indx( i - 1, p ) ] << ", " << sum[ j ] - sum[ p ] << " ) ) = ";
                best = min( best, max( dp[ indx( i - 1, p ) ], sum[ j ] - sum[ p ] ) );
                cout << best << endl;
            }

            dp[ indx( i , j ) ] = best;
            cout << "dp[ " << i << ", " << j << " ] = " << best << endl;
        }
    }

    // required
    return dp[ indx( k, n ) ];
}

int main( int argc, char* argv[] )
{
    /*int x = 12, y = 21;
    auto pow1 = power( x, y );*/

    //cout << "Last digit of Fib(14) = " << fib( 14 ) << endl;

    /*int arr1[] = { 2, 3, 6, 7, 9 };
    int arr2[] = { 1, 4, 8, 10 };
    cout << "kth element = " << kthElement( arr1, arr2, _countof( arr2 ), _countof( arr1 ), 5 );*/

    /*string a = "01011001111101001110101", b = "01000110010011011";
    cout << "binary prod = " << karatsubaAlgo( a, b ) << endl;*/

    int arr[] = { 10, 20, 60, 50, 30, 40 };
    int n = sizeof( arr ) / sizeof( arr[ 0 ] );
    int k = 3;
    cout << "findMax(arr, n, k) = " << findMax( arr, n, k ) << endl;
    
    return 0;
}