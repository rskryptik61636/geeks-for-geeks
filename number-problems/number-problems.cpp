#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// Source: https://practice.geeksforgeeks.org/problems/perfect-numbers3207/1
int pairCubeCount( int N )
{
    static constexpr bool debug = false;

    // Start with the cube root of N and N^3
    const int cbRoot = static_cast<int>( cbrt( static_cast<double>( N ) ) );
    const int nCubed = N * N * N;

    if( debug )
    {
        cout << "N = " << N << "; cbRoot(N) = " << cbRoot << "; n^3 = " << nCubed << endl;
    }

    // Consider a in [1, cbRoot]
    int count = 0;
    for( int a = 1; a <= cbRoot; ++a )
    {
        const int aCubed = ( a * a * a );
        if( debug )
        {
            cout << "a = " << a << "; a^3 = " << aCubed << endl;
        }

        // Consider b^3 = N - a^3
        const int bCubed = N - aCubed;
        const double b = ( bCubed != 0 ) ? cbrt( static_cast<double>( bCubed ) ) : 0.0;

        if( debug )
        {
            cout << "b = " << b << "; b^3 = " << bCubed << endl;
        }

        // Increment the sum if b's cube root is an integer value.
        if( ceil( b ) == floor( b ) )
        {
            ++count;

            if( debug )
            {
                cout << "count = " << count << endl;
            }
        }
    }

    return count;
}

// Source: https://practice.geeksforgeeks.org/problems/find-nth-root-of-m5843/1
int NthRoot( int n, int m )
{
    // nth root of m = m^(1/n)
    const int result = static_cast<int>( round( pow( static_cast<double>( m ), 1.0 / static_cast<double>( n ) ) ) );
    if( pow( result, n ) == m )
        return result;

    return -1;
}

// Source: https://practice.geeksforgeeks.org/problems/prime-number2314/1
int isPrime( int N )
{
    if( N == 1 )
    {
        return 0;
    }

    for( int i = 2; i <= sqrt( N ); i++ )
    {
        if( N % i == 0 )
        {
            return 0;
        }
    }

    return 1;
}

// Source: https://practice.geeksforgeeks.org/problems/sieve-of-eratosthenes5242/1#
vector<int> sieveOfEratosthenes( int N )
{
    static constexpr bool debugPrints = false;

    // Init the sieve.
    vector<bool> sieve( N - 1, true );

    // Iterate over the sieve and reset the bits of all the non-prime numbers.
    vector<int> result;
    for( int p = 2; p <= N; ++p )
    {
        if( debugPrints )
            cout << "p = " << p << endl;

        if( sieve[ p - 2 ] == true )
        {
            for( int i = 1; ( p * i ) <= N; ++i )
            {
                sieve[ ( p * i ) - 2 ] = false;

                if( debugPrints )
                    cout << "reset " << ( p * i ) << " at " << ( p * i ) - 2 << endl;
            }
            result.emplace_back( p );
        }
    }

    return result;
}

// Source: https://practice.geeksforgeeks.org/problems/sum-of-all-prime-numbers-between-1-and-n4404/1
long long int prime_Sum( int n )
{

    static constexpr bool debugPrints = false;

    // Init the sieve.
    vector<bool> sieve( n - 1, true );

    // Iterate over the sieve and reset the bits of all the non-prime numbers.
    long long int sum = 0;
    for( int p = 2; p <= n; ++p )
    {
        if( debugPrints )
            cout << "p = " << p << endl;

        if( sieve[ p - 2 ] == true )
        {
            for( int i = 1; ( p * i ) <= n; ++i )
            {
                sieve[ ( p * i ) - 2 ] = false;

                if( debugPrints )
                    cout << "reset " << ( p * i ) << " at " << ( p * i ) - 2 << endl;
            }
            sum += p;
        }
    }

    return sum;
}

// Source: https://www.geeksforgeeks.org/problems/minimum-number-of-jumps-1587115620/1?page=1&sortBy=submissions
int minJumps( int arr[], int n )
{
    // Your code here
    if( n <= 1 ) return 0;

    int coverage = 0, jump = 0, lastjumpindex = 0;
    for( int i = 0; i < n; i++ )
    {
        coverage = max( coverage, i + arr[ i ] );

        if( i == lastjumpindex )
        {
            jump++;
            lastjumpindex = coverage;

            if( coverage >= n - 1 ) return jump;
            if( i >= n - 1 ) return -1;
        }
    }
    return -1;
}

// Source: https://www.geeksforgeeks.org/problems/coin-change2448/1?page=1&sortBy=submissions
template<int n, int sum>
long long int count( int coins[] )
{

    // 2d table of solution space
    long long int t[ n + 1 ][ sum + 1 ];

    // First element of each row is 1, all other elements in the row are 0s
    for( int i = 0; i <= n; i++ ) { t[ i ][ 0 ] = 1; }
    for( int i = 1; i <= sum; i++ ) { t[ 0 ][ i ] = 0; }

    std::cout << "Table contents:\n";
    for( int i = 1; i <= n; i++ )
    {
        for( int j = 1; j <= sum; j++ )
        {

            // Current coin denomination <= sum
            if( coins[ i - 1 ] <= j )
            {
                t[ i ][ j ] = t[ i ][ j - coins[ i - 1 ] ] + t[ i - 1 ][ j ];
                std::cout << "b1," << t[ i ][ j ] << " = " << t[i][j - coins[i - 1]] << " + " << t[i - 1][j] << ";\t";
            }

            // Otherwise previous entry carries forward
            else
            {
                t[ i ][ j ] = t[ i - 1 ][ j ];
                std::cout << "b2," << t[ i ][ j ] << " = " << t[ i - 1 ][ j ] << ";\t";
            }

            //std::cout << t[ i ][ j ] << ",";
        }
        std::cout << std::endl;
    }
    return t[ n ][ sum ];
    // code here.
}

int cutRod( int price[], int n )
{
    //// Source: https://www.geeksforgeeks.org/problems/rod-cutting0840/1?page=1&sortBy=submissions
    //std::vector<int> dp( n + 1, 0 );
    //// From a length of 1 to n:
    //for( int i = 1; i <= n; i++ )
    //{
    //    // From a length of 0 to i
    //    for( int idx = 0; idx < i; idx++ )
    //    {
    //        // a = current max value of rod length i
    //        // b = current max value of rod length idx
    //        // c = price of rod length (i - idx)
    //        // max value of rod length i = max(a, b + c)
    //        const int a = dp[ i ], b = dp[ idx ], c = price[ i - idx - 1 ];
    //        dp[ i ] = max( dp[ i ], dp[ idx ] + price[ i - idx - 1 ] );
    //        std::cout << dp[ i ] << " = max( " << a << ", " << b << " + " << c << " )\n";
    //    }
    //    std::cout << std::endl;

    //    // DPF
    //    for( auto& n : dp )
    //        std::cout << n << ", ";
    //    std::cout << "\n\n";
    //}
    //return dp[ n ];

    // Source: Intro to Algos - bottom up solution
    std::vector<int> result( n + 1, std::numeric_limits<int>::min() );  // Init with lowest possible cost

    // Revenue of length 0 rod is 0
    result[ 0 ] = 0;

    // Solving subproblems of size [j, n]
    for( int j = 1; j <= n; ++j )
    {
        int currResult = std::numeric_limits<int>::min();

        // Solving subproblems of size [i, j]
        for( int i = 1; i <= j; ++i )
        {
            currResult = std::max( currResult, price[ i ] + result[ j - i ] );  // Best result = max( currResult, price[rod length i] + bestResult[rod length j - i]
        }

        // currResult = bestResult[j]
        result[ j ] = currResult;
    }

    return result[ n ];
}

int main( int argc, char* argv[] )
{
    //cout << "pairCubeCount(" << 1729 << ") = " << pairCubeCount( 1729 ) << endl;

    /*int coins[] = { 1, 2, 3 };
    auto coinCount = count<3, 4>( coins );
    std::cout << "N = 3, sum = 4, coinCount = " << coinCount << std::endl;*/

    int n = 8;
    //int price[] = { 1, 5, 8, 9, 10, 17, 17, 20 };
    int price[] = { 3, 5, 8, 9, 10, 17, 17, 20 };
    int rodPrice = cutRod( price, n );
    std::cout << "rodPrice = " << rodPrice << std::endl;
    
    return 0;
}