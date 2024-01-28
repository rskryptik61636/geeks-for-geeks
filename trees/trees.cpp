#include <vector>
#include <cmath>

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

int main()
{
    //// Test maxHeapify
    //std::vector<int> data{ 16, 4, 10, 14, 7, 9, 3, 2, 8, 1 };
    //maxHeapify(data, 1, data.size());

    //// Test buildMaxHeap
    //std::vector<int> data{ 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
    //buildMaxHeap(data);

    // Test heap sort
    std::vector<int> data{ 16, 4, 10, 14, 7, 9, 3, 2, 8, 1 };
    heapSort(data);

    return 0;
}