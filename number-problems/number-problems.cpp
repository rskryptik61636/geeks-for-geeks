#include <cmath>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <unordered_set>

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

// Source: https://www.geeksforgeeks.org/problems/sorting-elements-of-an-array-by-frequency/0
void frequencyBasedSort() 
{
    using Key = uint32_t;
    using Count = uint32_t;

    struct FrequencyPair
    {
        Key number;
        Count count;
    };

    struct FrequencyPairCompare
    {
        bool operator()(const FrequencyPair& a, const FrequencyPair& b) const
        {
            if (a.count != b.count)
            {
                return a.count > b.count;
            }

            return a.number <= b.number;
        }
    };

    // Get the test case count
    cout << "Enter the test case count: ";
    uint32_t tc = 0;
    cin >> tc;

    // For each test case...
    for (auto t = 0; t < tc; ++t)
    {
        // Read in the number of elements.
        cout << "Enter the number of elements: ";
        uint32_t n = 0;
        cin >> n;

        // Create a map<Key, Count> where:
        // Key = input number
        // Count = frequency
        std::vector<uint32_t> nums(n, 0);
        std::map<Key, Count> freqs;
        std::cout << "Enter the numbers: ";
        for (auto i = 0; i < n; ++i)
        {
            uint32_t cn = 0;
            cin >> cn;
            if (freqs.find(cn) == freqs.end())
            {
                freqs[cn] = 0;
            }
            ++freqs[cn];
            //nums[i] = cn;
        }

        // Create a set of FrequencyPairs with FrequencyPairCompare as the comparison function.
        std::set<FrequencyPair, FrequencyPairCompare> sortedSet;
        for (auto i = freqs.begin(); i != freqs.end(); ++i)
        {
            sortedSet.insert({ i->first, i->second });
        }

        // Print out the frequency based sorted elements.
        cout << "Frequency based sorted elements: ";
        for (auto i = sortedSet.begin(); i != sortedSet.end(); ++i)
        {
            for (auto j = 0; j < i->count; ++j)
            {
                cout << i->number << " ";
            }
        }
        cout << endl;
    }
}

// Source: https://www.educative.io/blog/apple-coding-interview-questions#array
// 3 tuple sum: Runtime Complexity: Quadratic, Memory Complexity : Constant
bool find_sum_of_two(vector<int>& A, int val, size_t start_index) 
{
    for (int i = start_index, j = A.size() - 1; i < j;) {
        int sum = A[i] + A[j];
        if (sum == val) {
            return true;
        }

        if (sum < val) {
            ++i;
        }
        else {
            --j;
        }
    }

    return false;
}

bool find_sum_of_three_v3(vector<int> arr, int required_sum) {

    std::sort(arr.begin(), arr.end());

    for (int i = 0; i < arr.size() - 2; ++i) {
        int remaining_sum = required_sum - arr[i];
        if (find_sum_of_two(arr, remaining_sum, i + 1)) {
            return true;
        }
    }

    return false;
}

// Merged intervals: Complexity: O(n); Memory: O(n)
class Pair 
{
public:
    int first, second;
    Pair(int x, int y) {
        first = x;
        second = y;
    }
};

vector<Pair> merge_intervals(vector<Pair>& v) 
{

    if (v.size() == 0) {
        return v;
    }

    vector<Pair> result;
    result.push_back(Pair(v[0].first, v[0].second));

    for (int i = 1; i < v.size(); i++) {
        int x1 = v[i].first;
        int y1 = v[i].second;
        int x2 = result[result.size() - 1].first;
        int y2 = result[result.size() - 1].second;

        if (y2 >= x1) {
            result[result.size() - 1].second = max(y1, y2);
        }
        else {
            result.push_back(Pair(x1, y1));
        }
    }
    return result;
}

// Stolen from: https://www.geeksforgeeks.org/array-rotation/
// Function to reverse array elements from start to end
void reverse(vector<int>& arr, int start, int end) {
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

// Function to left rotate array elements by d positions
void leftRotate(vector<int>& arr, int d) {
    int n = arr.size();
    d = d % n; // To handle case when d >= n

    // Reverse the first d elements
    reverse(arr, 0, d - 1);
    // Reverse the remaining elements
    reverse(arr, d, n - 1);
    // Reverse the whole array
    reverse(arr, 0, n - 1);
}

// Returns number of pairs in arr[0..n-1] with sum equal
// to 'sum'
int getPairsCount(int arr[], int n, int k)
{
    std::unordered_set<int> s;
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (s.find(k - arr[i]) != s.end()) {
            count++;
        }
        else
            s.insert(k - arr[i]);
    }
    return count;
}

int main( int argc, char* argv[] )
{
    //cout << "pairCubeCount(" << 1729 << ") = " << pairCubeCount( 1729 ) << endl;

    /*int coins[] = { 1, 2, 3 };
    auto coinCount = count<3, 4>( coins );
    std::cout << "N = 3, sum = 4, coinCount = " << coinCount << std::endl;*/

    //int n = 8;
    ////int price[] = { 1, 5, 8, 9, 10, 17, 17, 20 };
    //int price[] = { 3, 5, 8, 9, 10, 17, 17, 20 };
    //int rodPrice = cutRod( price, n );
    //std::cout << "rodPrice = " << rodPrice << std::endl;

    frequencyBasedSort();
    
    return 0;
}