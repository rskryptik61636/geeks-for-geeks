#include <cstdlib>

int closestNumber( int N, int M )
{

    // Store flag if N is negative.
    const bool negativeN = ( N < 0 );

    // Make M absolute in case its negative.
    M = abs( static_cast<double>( M ) );

    // Early out if N is divisible by M.
    if( ( N % M ) == 0 )
    {
        return N;
    }

    // Integer divide gets us the dividend floor.
    const int dividend = N / M;
    const int ceiling = M * ( negativeN ? ( dividend - 1 ) : ( dividend + 1 ) );
    const int floor1 = M * dividend;

    // Take the abs diff.
    const int ceilDiff = abs( ceiling - N );
    const int floorDiff = abs( N - floor1 );

    // If they're equal, return the one with the larger absolute value.
    if( ceilDiff == floorDiff )
    {
        return abs( static_cast<double>( ceiling ) ) > abs( static_cast<double>( floor1 ) ) ? ceiling : floor1;
    }

    // Return the number with the lower diff.
    return ( ceilDiff < floorDiff ) ? ceiling : floor1;
}

int main( int argc, char* argv[] )
{
    return 0;
}