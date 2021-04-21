#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

enum class Test
{
    Test_FirstSetBit,
    Test_RightmostDiffBit
};

/*  function to find position of first set
bit in the given number
 * n: given input for which we want to get
      the position of first set bit
 */
unsigned int getFirstSetBit( int n )
{

    // Your code here
    if( n >= 1 )
    {
        int a = n ^ ( n - 1 );  // XOR(n, n-1) gives the first set bit which is different between the two, which should be the first set bit of n.
        return static_cast<unsigned int>( log2f( static_cast<float>( a ) + 1 ) );   // log2(a) gives the location of the first set bit.
    }

    return 0;

}

/*  Function to find the first position with different bits
 *   This function returns the position with different bit
 */
int posOfRightMostDiffBit( int m, int n )
{

    // Your code here
    if( m == n )
        return -1;

    return getFirstSetBit( m ^ n );

}

bool checkKthBit( int n, int k )
{

    // Your code here
    // It can be a one liner logic!! Think of it!!
    const int kBit = ( 1 << k );
    return ( ( n & kBit ) == kBit );
}

int toggleBits( int N, int L, int R )
{
    // code here
    const int mask = ( ( 1 << R ) - 1 ) ^ ( ( 1 << ( L - 1 ) ) - 1 );   // masks out bits (L, R]. Might be an issue in the problem as it should be (1 << L) and not (1 << (L - 1)).
    return N ^ mask;    // N ^ mask toggles the mask bits in N
}

int setKthBit( int N, int K )
{
    // Write Your Code here
    return N | ( 1 << K );
}

// Function to check if given number n is a power of two.
bool isPowerofTwo( long long n )
{

    // Special case 0.
    if( n == 0 )
        return false;

    // Only 1 bit should be set in n if it is a power of 2. ~( n - 1 ) sets all the prior bits so n & ~(n-1) should equal n if it is a power of 2.
    return ( n & ~( n - 1 ) ) == n; 
}

// Function to find number of bits needed to be flipped to convert A to B
int countBitsFlip( int a, int b )
{

    // Your logic here
    int mask = a ^ b; // mask contains all the bits that need to be flipped to turn A into B

    int count = 0;
    while( mask > 0 )
    {
        mask &= ( mask - 1 ); // mask & (mask - 1) decrements the no. of set bits in mask.
        ++count;
    }

    return count;

}

// Rotate 16-bit n by d bits left and right. Store left rotate and right rotate in the result.
// Ref: https://stackoverflow.com/questions/776508/best-practices-for-circular-shift-rotate-operations-in-c
vector <int> rotate( int n, int d )
{
    //code here.
    const int oobMask = ( -d & 15 );  // Wrap-around mask. 15 is 16 - 1.
    const int leftRotate = ( ( n << d ) | ( n >> oobMask ) ) & 0xffff;    // & 0xffff since n is a 16 bits wide integer stored in a 32 bit int
    const int rightRotate = ( ( n >> d ) | ( n << oobMask ) ) & 0xffff;
    vector<int> result{ leftRotate, rightRotate };
    return result;
}

// function to swap odd and even bits
unsigned int swapBits( unsigned int n )
{
    typedef unsigned int uint;
    static const uint evenBitsMask = 0xAAAAAAAA;
    static const uint oddBitsMask = 0x55555555;
    uint evenBits = n & evenBitsMask;   // Masks of the even and odd bits in n.
    uint oddBits = n & oddBitsMask;
    evenBits >>= 1; // Right shift even bits by 1 and left shift odd bits by 1 to get the swapped bits.
    oddBits <<= 1;
    return ( evenBits | oddBits );
}

// n: input to count the number of set bits
//Function to return sum of count of set bits in the integers from 1 to n.
int countSetBits( int n )
{
    // Stolen from here: https://www.geeksforgeeks.org/count-total-set-bits-in-all-numbers-from-1-to-n/
    int two = 2, ans = 0;
    int n2 = n;
    while( n2 )
    {
        ans += ( n / two ) * ( two >> 1 );
        if( ( n & ( two - 1 ) ) > ( two >> 1 ) - 1 ) ans += ( n & ( two - 1 ) ) - ( two >> 1 ) + 1;
        two <<= 1;
        n2 >>= 1;
    }
    return ans;
}

// Stolen from https://www.geeksforgeeks.org/find-the-number-occurring-odd-number-of-times/
int getOddOccurrence( int arr[], int n )
{
    int res = arr[ 0 ];
    for( int i = 1; i < n; ++i )
    {
        res ^= arr[ i ];
    }
    return res;
}

int main( int argc, char* argv )
{
    Test test = Test::Test_RightmostDiffBit;

    switch( test )
    {
    case Test::Test_FirstSetBit:
        int num;
        std::cout << "Enter an integer: ";
        std::cin >> num;
        std::cout << "First set bit = " << getFirstSetBit( num ) << std::endl;
        break;

    case Test::Test_RightmostDiffBit:
        int m, n;
        std::cout << "Enter two integers and hit enter after each one: ";
        std::cin >> m;
        std::cin >> n;
        std::cout << "Right most diff bit = " << posOfRightMostDiffBit( m, n ) << std::endl;
        break;
    }

    return 0;
}