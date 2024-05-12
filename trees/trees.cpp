#include <vector>
#include <queue>
#include <cmath>

using namespace std;

// Get left\right children indices
std::size_t left(const std::size_t i) { return 2 * i + 1; }
std::size_t right(const std::size_t i) { return 2 * i + 2; }

// Max heapify: Complexity = lg(n)
void maxHeapify(std::vector<int>& data, std::size_t i, std::size_t n)
{
    // Requirement is that l and r are roots of max heaps.
    auto l = left(i), r = right(i);
    auto largest = i;
    if (l < n && data[l] > data[i])
        largest = l;
    if (r < n && data[r] > data[largest])
        largest = r;
    if (largest != i)
    {
        std::swap(data[i], data[largest]);
        maxHeapify(data, largest, n);
    }
}

// Build max heap: Complexity = Upper bound O(n*lgn). Tigher bound is O(n) since most work is done only on half the elements of the tree (rest are leaves).
void buildMaxHeap(std::vector<int>& data)
{
    // Start at floor(n/2) and maxHeapify from there till the root.
    // Can start at n/2 since all nodes past that point are leaves of the tree
    // which are by themselves max heaps.
    for (int i = static_cast<int>(data.size()) / 2; i >= 0; --i)
        maxHeapify(data, static_cast<std::size_t>(i), data.size());
}

// Heap sort. Complexity = O(n * lgn). n = buildMaxHeap, lg(n) for each of the maxHeapify calls.
void heapSort(std::vector<int>& data)
{
    // First build the max heap
    buildMaxHeap(data);

    // Traverse the array backwards until the 2nd element.
    for (auto i = data.size() - 1; i > 0; --i)
    {
        // Swap the first and i'th elements to move the largest element to the i'th position.
        std::swap(data[0], data[i]);

        // Max heapify from data[0, i)
        maxHeapify(data, 0, i);
    }
}

// function to convert the array to BST
// and return the root of the created tree
vector<size_t> sortedArrayToBST(vector<size_t>& nums)
{
    // if the array is empty return NULL
    if (nums.empty()) {
        return vector<size_t>();
    }

    constexpr size_t nullIndx = -1;
    auto n = nums.size();

    /* Algorithm:
    * - Pick mid value of sorted array as root
    * - Left child = midpoint of left half; Right child = midpoint of right half
    * - RootIndx = 0. Set root, left and right children in result.
    *
    * Sample traversal:
    * 1, 2, 3, 4, 5, 6, 7

        result: -1, -1, -1, -1, -1, -1, -1
        root: 4, lc: 2, rc: 6
        result: 4, 2, 6, -1, -1, -1, -1
        queue: {(indx1, {indx0, indxNULL}), (indx5, {indx4, indx6})}

        curr = (indx1, {indx0, indxNULL})
        root: 2, lc: 1, rc: 3
        result: 4, 2, 6, 1, 3, -1, -1
            No subtree for indx0, skip

        curr = (indx5, {indx4, indx6})
        root: 6, lc: 5, rc: 7
        result: 4, 2, 6, 1, 3, 5, 7
    */

    // BST in array form
    // Left child: 2*i + 1
    // Right child: 2*i + 2
    vector<size_t> result(n, nullIndx);
    auto fnGetTargetLeftChildIndx = [](const size_t i) { return 2 * i + 1; };
    auto fnGetTargetRightChildIndx = [](const size_t i) { return 2 * i + 2; };
    struct Node
    {
        size_t dstParentIndx, start, end;
    };
    queue<Node> traversal;

    // Traversal update function
    auto fnUpdateTraversal = [&](const size_t dstParentIndx, const size_t left, const size_t right)
    {
        // Proceed only if left != right
        if (left != right)
        {
            auto mid = (left + right) >> 1;
            auto srcParentIndx = mid;
            auto srcLeftChildIndx = (left + mid - 1) >> 1;
            auto srcRightChildIndx = (mid + 1 + right) >> 1;

            auto dstLeftChildIndx = fnGetTargetLeftChildIndx(dstParentIndx);
            auto dstRightChildIndx = fnGetTargetRightChildIndx(dstParentIndx);

            result[dstParentIndx] = nums[srcParentIndx];
            result[dstLeftChildIndx] = nums[srcLeftChildIndx];
            result[dstRightChildIndx] = nums[srcRightChildIndx];

            // Push left child subtree only if valid
            if (left != srcParentIndx - 1)
            {
                traversal.push({ dstLeftChildIndx, left, srcParentIndx - 1 });
            }

            if (right != srcParentIndx + 1)
            {
                traversal.push({ dstRightChildIndx, srcParentIndx + 1, right });
            }
        }
    };

    // Mid point as root
    auto start = 0;
    auto end = n - 1;
    fnUpdateTraversal(0, start, end);

    // Traverse subtrees until complete.
    while (!traversal.empty())
    {
        auto currNode = traversal.front();
        traversal.pop();

        fnUpdateTraversal(currNode.dstParentIndx, currNode.start, currNode.end);
    }

    return result;
}

int main()
{
    //// Test maxHeapify
    //std::vector<int> data{ 16, 4, 10, 14, 7, 9, 3, 2, 8, 1 };
    //maxHeapify(data, 1, data.size());

    //// Test buildMaxHeap
    //std::vector<int> data{ 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
    //buildMaxHeap(data);

    //// Test heap sort
    //std::vector<int> data{ 16, 4, 10, 14, 7, 9, 3, 2, 8, 1 };
    //heapSort(data);

    // Test sortedArrayToBst
    vector<size_t> nums = { 1, 2, 3, 4, 5, 6, 7 };
    auto bst = sortedArrayToBST(nums);

    return 0;
}