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

int main( int argc, char* argv[] )
{
    cout << "pairCubeCount(" << 1729 << ") = " << pairCubeCount( 1729 ) << endl;
    return 0;
}