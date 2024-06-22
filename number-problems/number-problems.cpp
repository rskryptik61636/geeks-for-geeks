#include <cmath>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <unordered_set>
#include <stack>

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

// Towers of Hanoi: https://www.geeksforgeeks.org/iterative-tower-of-hanoi/
char rod[] = { 'S', 'A', 'D' };
vector<stack<int>> stacks(3); // 3 stacks for 3 rods

void moveDisk(int a, int b)
{
    if (stacks[b].empty() || (!stacks[a].empty() && stacks[a].top() < stacks[b].top()))
    {
        cout << "Move disk " << stacks[a].top() << " from rod " << rod[a] << " to rod " << rod[b] << "\n";
        stacks[b].push(stacks[a].top());
        stacks[a].pop();
    }
    else
        moveDisk(b, a);
}

void towerOfHanoi(int n)
{
    cout << "Tower of Hanoi for " << n << " disks:\n";

    int src = 0, aux = 1, dest = 2;
    for (int i = n; i > 0; i--)
        stacks[src].push(i);

    int totalMoves = (1 << n) - 1;
    if (n % 2 == 0)
        swap(aux, dest);

    for (int i = 1; i <= totalMoves; i++)
    {
        if (i % 3 == 0)
            moveDisk(aux, dest);
        else if (i % 3 == 1)
            moveDisk(src, dest);
        else
            moveDisk(src, aux);
    }
}

/*
Certainly! Let's dive into how the multiplication program using bitwise operators works. We'll break it down step by step:

1. **Input Validation**:
   - The `multiply` function takes two integer inputs: `a` and `b`.
   - We assume that both `a` and `b` are non-negative integers (since negative numbers would require additional handling).

2. **Binary Multiplication Algorithm**:
   - The goal is to compute the product of `a` and `b` using only addition and bitwise operations.
   - We initialize a variable called `result` to store the final product.

3. **Bitwise AND (`&`) Operation**:
   - The expression `b & 1` checks whether the least significant bit (LSB) of `b` is set (i.e., whether it is equal to 1).
   - If the LSB of `b` is 1, we add the current value of `a` to the `result`.
   - Otherwise, we skip adding anything to the result.

4. **Left Shift (`<<`) Operation**:
   - We left shift `a` by 1 (equivalent to multiplying it by 2).
   - This effectively doubles the value of `a`.

5. **Right Shift (`>>`) Operation**:
   - We right shift `b` by 1 (equivalent to dividing it by 2).
   - This effectively discards the LSB of `b`.

6. **Repeat Until `b` Becomes 0**:
   - We continue the process until `b` becomes 0 (i.e., all bits of `b` have been processed).
   - In each iteration, we check the LSB of `b` using `b & 1`.
   - If it's 1, we add the current value of `a` to the result.
   - Then we update `a` by left shifting it, and `b` by right shifting it.

7. **Final Result**:
   - The final value of `result` represents the product of `a` and `b`.

Here's an example:
- Suppose we want to multiply `a = 5` and `b = 3`.
- Binary representation:
  - `5` (a) = `0101`
  - `3` (b) = `0011`
- Iterations:
  - First iteration: `b & 1` evaluates to 1 (LSB of `b` is 1), so we add `a` to the result.
  - Update `a` by left shifting: `a = 10` (binary: `1010`).
  - Update `b` by right shifting: `b = 1` (binary: `0001`).
  - Second iteration: `b & 1` evaluates to 1, so we add the updated `a` (which is 10) to the result.
  - Update `a` by left shifting: `a = 20` (binary: `10100`).
  - Update `b` by right shifting: `b = 0` (binary: `0000`).
- Result: `result = 15` (binary: `1111`), which is the correct answer.
*/
int multiply(int a, int b) {
    int result = 0;
    while (b > 0) {
        if (b & 1) {
            result += a;
        }
        a <<= 1; // Left shift a by 1 (equivalent to multiplying by 2)
        b >>= 1; // Right shift b by 1 (equivalent to dividing by 2)
    }
    return result;
}

/*
* Certainly! Let's dive into how the division program using bitwise operators works. We'll break it down step by step:

1. **Input Validation**:
   - The `divide` function takes two integer inputs: `dividend` and `divisor`.
   - We handle the case where the divisor is zero to avoid division by zero errors.

2. **Sign Handling**:
   - We determine the sign of the result (`quotient`) based on whether the dividend and divisor have the same sign or opposite signs.
   - If they have opposite signs, the result will be negative; otherwise, it will be positive.

3. **Conversion to Positive Numbers**:
   - We work with the absolute values of the dividend and divisor (using `std::abs`).
   - This ensures that we handle the division correctly regardless of the original signs.

4. **Binary Long Division**:
   - We perform binary long division, similar to how we do it manually.
   - Start with the dividend (`num`) and divisor (`den`).
   - Initialize the `quotient` as 0.

5. **Iterate Through Bits**:
   - We iterate through the bits of the dividend (from left to right).
   - For each bit position (from 31 to 0):
     - If `(num >> i) >= den`, we subtract `den << i` from `num` and set the corresponding bit in the `quotient`.
     - Otherwise, we skip that bit.

6. **Shifts and Subtractions**:
   - The left shift (`<<`) effectively multiplies `den` by 2 for each iteration.
   - The subtraction (`num -= (den << i)`) reduces the remaining value of `num`.

7. **Result**:
   - The final value of `quotient` represents the result of the division.

Here's an example:
- Suppose we want to divide 15 by 3.
- Binary representation:
  - `15` (dividend) = `1111`
  - `3` (divisor) = `0011`
- Iterations:
  - First iteration: `(15 >> 3) = 1 >= 3`, so subtract `3 << 3` from `15` and set the 3rd bit in the quotient.
  - Second iteration: `(15 >> 2) = 3 >= 3`, so subtract `3 << 2` from the updated `15` and set the 2nd bit in the quotient.
  - Third iteration: `(15 >> 1) = 7 >= 3`, so subtract `3 << 1` from the updated `15` and set the 1st bit in the quotient.
  - Fourth iteration: `(15 >> 0) = 15 >= 3`, so subtract `3 << 0` from the updated `15` and set the 0th bit in the quotient.
- Result: `quotient = 5` (binary: `0101`), which is the correct answer.
*/
int divide(int dividend, int divisor) {
    if (divisor == 0) {
        std::cerr << "Error: Division by zero!" << std::endl;
        return 0;
    }

    int sign = 1;
    if ((dividend < 0) ^ (divisor < 0)) {
        sign = -1;
    }

    long long num = std::abs(static_cast<long long>(dividend));
    long long den = std::abs(static_cast<long long>(divisor));

    long long quotient = 0;
    for (int i = 31; i >= 0; --i) {
        if ((num >> i) >= den) {    // den is divisible by 2^i
            quotient |= (1LL << i); // quotient is updated with 2^i
            num -= (den << i);      // num is reduced by 2*i*den
        }
    }

    return static_cast<int>(sign * quotient);
}

// C++ program to Find the repeating
// and missing elements
// Source: https://www.geeksforgeeks.org/find-a-repeating-and-a-missing-number/
void printTwoElements(int arr[], int size)
{
    int i;
    cout << "The repeating element is ";

    for (i = 0; i < size; i++) {
        if (arr[abs(arr[i]) - 1] > 0)
            arr[abs(arr[i]) - 1] = -arr[abs(arr[i]) - 1];
        else
            cout << abs(arr[i]) << "\n";
    }

    cout << "and the missing element is ";
    for (i = 0; i < size; i++) {
        if (arr[i] > 0)
            cout << (i + 1);
    }
}

/* Function to print product array
for a given array arr[] of size n */

// Source: https://www.geeksforgeeks.org/a-product-array-puzzle/
// This code is contributed by rathbhupendra
void productArray(int arr[], int n)
{

    // Base case 
    if (n == 1) {
        cout << 0;
        return;
    }

    int i, temp = 1;

    /* Allocate memory for the product array */
    //int* prod = new int[(sizeof(int) * n)];
    vector<int> prod(n, 1);

    ///* Initialize the product array as 1 */
    //memset(prod, 1, n);

    /* In this loop, temp variable contains product of
    elements on left side excluding arr[i] */
    for (i = 0; i < n; i++) {
        prod[i] = temp;
        temp *= arr[i];
    }

    /* Initialize temp to 1
    for product on right side */
    temp = 1;

    /* In this loop, temp variable contains product of
    elements on right side excluding arr[i] */
    for (i = n - 1; i >= 0; i--) {
        prod[i] *= temp;
        temp *= arr[i];
    }

    /* print the constructed prod array */
    for (i = 0; i < n; i++)
        cout << prod[i] << " ";

    return;
}

// Source: https://www.geeksforgeeks.org/majority-element/
int majorityElement(vector<int>& nums) {
    int num_bits = 32;
    int majority_element = 0;

    for (int i = 0; i < num_bits; ++i) {
        int count_ones = 0, count_zeros = 0;

        for (int num : nums) {
            if ((num >> i) & 1)
                count_ones++;
            else
                count_zeros++;
        }

        // The element that occurred the most times would have the most bits set overall at each position 'i'
        if (count_ones > count_zeros)
            majority_element |= (1 << i);
    }

    int count_majority = 0;
    for (int num : nums) {
        if (num == majority_element)
            count_majority++;
    }

    return count_majority > nums.size() / 2 ? majority_element : -1;
}

// Rotate a 2D array clockwise by 90 degrees
// Source: https://www.geeksforgeeks.org/rotate-a-matrix-by-90-degree-in-clockwise-direction-without-using-any-extra-space/
template<const uint32_t N>
void rotate90Clockwise(int arr[N][N])
{
    /* Move each element to its correponding location starting from the outermost square to the innermost.
    * Work in sets of 4 corresponding numbers and move each one to its target position using a temp variable 
    * -to store the first number to prevent it from being overwritten.
    * Input:
        1  2  3 4
         5  6  7 8
         9 10 11 12
        13 14 15 16
        
      Output:
        13 9 5 1
        14 10 6 2
        15 11 7 3
        16 12 8 4
    */
    // Traverse each cycle
    for (int x = 0; x < N / 2; x++) 
    {
        for (int y = x; y < N - x - 1; y++) 
        {
            // Swap elements of each cycle
            // in clockwise direction
            int temp = arr[x][y];
            arr[x][y] = arr[N - 1 - y][x];                  // top-left = bottom-left
            arr[N - 1 - y][x] = arr[N - 1 - x][N - 1 - y];  // bottom-left = bottom-right
            arr[N - 1 - x][N - 1 - y] = arr[y][N - 1 - x];  // bottom-right = top-right
            arr[y][N - 1 - x] = temp;                       // top-right = top-left
        }
    }
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

    //frequencyBasedSort();

 /*   int num1 = 15;
    int num2 = 3;
    std::cout << num1 << " * " << num2 << " = " << divide(num1, num2) << std::endl;*/

 /*   int arr[] = { 7, 3, 4, 5, 5, 6, 2 };
    int n = sizeof(arr) / sizeof(arr[0]);
    printTwoElements(arr, n);*/

    //int arr[] = { 10, 3, 5, 6, 2 };
    //int n = sizeof(arr) / sizeof(arr[0]);
    //cout << "The product array is: \n";
    //productArray(arr, n);

    /*vector<int> nums = { 3, 3, 4, 2, 4, 4, 2, 4, 4 };
    int result = majorityElement(nums);
    if (result != -1)
        cout << "Majority Element: " << result << endl;
    else
        cout << "No Majority Element" << endl;*/

    static const uint32_t N = 4;
    int arr[N][N] = { { 1, 2, 3, 4 },
                      { 5, 6, 7, 8 },
                      { 9, 10, 11, 12 },
                      { 13, 14, 15, 16 } };
    rotate90Clockwise<N>(arr);

    return 0;
}