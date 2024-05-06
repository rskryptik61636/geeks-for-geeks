#include <string>
#include <vector>
#include <set>
#include <stdexcept>
#include <algorithm>

using namespace std;

// Source: https://practice.geeksforgeeks.org/problems/implement-strstr/1
/* The function should return position where the target string
   matches the string str
Your are required to complete this method */
int strstr( string s, string x )
{
    auto findPos = s.find( x );

    return ( ( findPos == string::npos ) ? -1 : findPos );
}

/* 
Source: https://practice.geeksforgeeks.org/problems/check-for-subsequence4930/1#
The function returns true if A is a subsequence of B (A's chars appear in B in-order but maybe not contiguously.

Example 1:
Input:
A = AXY
B = YADXCP
Output: 0
Explanation: A is not a subsequence of B
as 'Y' appears before 'A'.

Example 2:
Input:
A = gksrek
B = geeksforgeeks
Output: 1
Explanation: A is a subsequence of B.

*/
bool isSubSequence( string A, string B )
{
    size_t aIter = 0;
    for( auto i = 0; i < B.size(); ++i )
    {
        if( B[ i ] == A[ aIter ] )
            ++aIter;
    }

    return ( aIter == A.size() );
}

/*  Source: https://practice.geeksforgeeks.org/problems/check-if-strings-are-rotations-of-each-other-or-not-1587115620/1
    Function to check if two strings are rotations of each other
*   s1, s2: are the input strings
*/
bool areRotations( string s1, string s2 )
{
    /* Two conditions must be satisfied:
        1. s1 and s2 must be of equal length.
        2. concat(s1, s1) must contain s2.
    */
    return
        ( s1.length() == s2.length() &&
            ( string( s1 + s1 ).find( s2 ) != string::npos ) );
}

/* Source: https://practice.geeksforgeeks.org/problems/check-if-two-strings-are-k-anagrams-or-not/1
Complete the function below*/
bool areKAnagrams( string str1, string str2, int k )
{
    // Early out if str1\2 are of unequal length.
    if( str1.length() != str2.length() )
        return false;

    // The no. of differing characters <= k for success.
    int diffCount = 0;
    for( auto i = str1.cbegin(); i != str1.cend(); ++i )
    {
        if( str2.find( *i ) == string::npos )
            ++diffCount;
    }

    return ( diffCount <= k );
}

// Source: https://practice.geeksforgeeks.org/problems/find-k-th-character-in-string3841/1
char kthCharacter( int m, int n, int k )
{
    // Convert m to a binary string
    string mBin;
    int mTmp = m;
    while( mTmp != 0 )
    {
        // Insert a '1' at the beginning if the LSB is 1, else insert '0'.
        if( ( mTmp & 1 ) != 0 )
            mBin.insert( 0, 1, '1' );
        else
            mBin.insert( 0, 1, '0' );

        // Right shift by 1 to test the next bit.
        mTmp >>= 1;
    }

    // Account for m == 0
    if( mTmp == m )
    {
        mBin = "0";
    }

    // Perform the transformation.
    string prev = mBin, next;
    for( auto i = 0; i < n; ++i )
    {
        next.clear();
        for( auto j = 0; j < prev.size(); ++j )
        {
            if( prev[ j ] == '1' )
                next.append( "10" );
            else
                next.append( "01" );
        }
        prev = next;
    }

    // Return the k'th char of prev.
    return prev[ k - 1 ];
}

// Source: https://www.geeksforgeeks.org/problems/permutations-of-a-given-string2041/1
std::vector<string> find_permutation(const string& S) {

    std::set<string> ans;

    auto solve = [&](auto&& solve, const string & S, string cur, std::vector<int>&vis)
    {
        if (cur.length() == S.length()) {
            ans.insert(cur);
            return;
        }

        for (int i = 0; i < S.length(); i++) {
            if (!vis[i]) {
                vis[i] = 1;
                solve(solve, S, cur + S[i], vis);
                vis[i] = 0;
            }
        }
    };

    std::vector<int> vis(S.length(), 0);
    string str;
    solve(solve, S, str, vis);
    return std::vector<string>(ans.begin(), ans.end());
}

// Validate IP address
bool validIPAddress(std::string address)
{
    bool result = true;

    // There should be only 3 '.'
    unsigned nDelim = 0;
    auto pos = address.begin();
    do
    {
        auto prevPos = pos;
        pos = std::find(prevPos, address.end(), '.');   // Skip ahead past the '.' if the first delim has been found
        if (pos != address.end())
        {
            try
            {
                const auto currNumStr = std::string(prevPos, pos);
                const auto currNum = std::stoul(currNumStr);
                if (currNum > 255)
                {
                    return false;   // No. must be in [0, 255]
                }
            }
            catch (const std::invalid_argument&)
            {
                // Not a valid number.
                return false;
            }
            ++nDelim;
            ++pos;  // Skip past the '.'
        }
    } while (pos != address.end());

    if (nDelim != 3)
        return false;

    return result;
}

int main( int argc, char* argv[] )
{
    //bool test = validIPAddress("192.0.1.1");
    bool test = validIPAddress("168.5.1.5.7");
    return 0;
}