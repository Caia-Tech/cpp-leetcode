#include <gtest/gtest.h>
#include "../../src/medium/top_k_frequent_elements.h"
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>

namespace leetcode {
namespace medium {
namespace test {

class TopKFrequentElementsTest : public ::testing::Test {
protected:
    TopKFrequentElements solution;
    
    // Helper function to check if result contains exactly k elements
    bool hasCorrectSize(const std::vector<int>& result, int k) {
        return result.size() == k;
    }
    
    // Helper function to check if all elements in result are unique
    bool hasUniqueElements(const std::vector<int>& result) {
        std::unordered_set<int> seen;
        for (int num : result) {
            if (seen.count(num)) return false;
            seen.insert(num);
        }
        return true;
    }
    
    // Helper function to count frequency in original array
    std::unordered_map<int, int> countFrequencies(const std::vector<int>& nums) {
        std::unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }
        return freq;
    }
    
    // Helper function to verify result has top k frequencies
    bool hasTopKFrequencies(const std::vector<int>& nums, const std::vector<int>& result, int k) {
        if (result.size() != k) return false;
        
        auto freq = countFrequencies(nums);
        
        // Get frequencies of result elements
        std::vector<int> resultFreqs;
        for (int num : result) {
            if (freq.find(num) == freq.end()) return false; // Element not in original array
            resultFreqs.push_back(freq[num]);
        }
        
        // Get all frequencies and sort them in descending order
        std::vector<int> allFreqs;
        for (const auto& pair : freq) {
            allFreqs.push_back(pair.second);
        }
        std::sort(allFreqs.begin(), allFreqs.end(), std::greater<int>());
        
        // Sort result frequencies in descending order
        std::sort(resultFreqs.begin(), resultFreqs.end(), std::greater<int>());
        
        // Check if result frequencies match top k frequencies from original
        // We need to handle ties properly - any elements with the kth frequency are valid
        std::multiset<int> topKFreqs;
        for (int i = 0; i < k && i < allFreqs.size(); i++) {
            topKFreqs.insert(allFreqs[i]);
        }
        
        std::multiset<int> resultFreqSet;
        for (int freq : resultFreqs) {
            resultFreqSet.insert(freq);
        }
        
        return topKFreqs == resultFreqSet;
    }
    
    // Helper function to test all approaches
    void testAllApproaches(std::vector<int> nums, int k) {
        // Make copies for each approach since some modify the input
        std::vector<int> nums1 = nums, nums2 = nums, nums3 = nums;
        std::vector<int> nums4 = nums, nums5 = nums, nums6 = nums;
        
        auto result1 = solution.topKFrequent(nums1, k);
        auto result2 = solution.topKFrequentQuickSelect(nums2, k);
        auto result3 = solution.topKFrequentBucketSort(nums3, k);
        auto result4 = solution.topKFrequentMaxHeap(nums4, k);
        auto result5 = solution.topKFrequentSort(nums5, k);
        auto result6 = solution.topKFrequentCountingSort(nums6, k);
        
        // All results should have correct size
        EXPECT_TRUE(hasCorrectSize(result1, k)) << "Min-Heap approach size incorrect";
        EXPECT_TRUE(hasCorrectSize(result2, k)) << "QuickSelect approach size incorrect";
        EXPECT_TRUE(hasCorrectSize(result3, k)) << "Bucket Sort approach size incorrect";
        EXPECT_TRUE(hasCorrectSize(result4, k)) << "Max-Heap approach size incorrect";
        EXPECT_TRUE(hasCorrectSize(result5, k)) << "Sorting approach size incorrect";
        EXPECT_TRUE(hasCorrectSize(result6, k)) << "Counting Sort approach size incorrect";
        
        // All results should have unique elements
        EXPECT_TRUE(hasUniqueElements(result1)) << "Min-Heap approach has duplicates";
        EXPECT_TRUE(hasUniqueElements(result2)) << "QuickSelect approach has duplicates";
        EXPECT_TRUE(hasUniqueElements(result3)) << "Bucket Sort approach has duplicates";
        EXPECT_TRUE(hasUniqueElements(result4)) << "Max-Heap approach has duplicates";
        EXPECT_TRUE(hasUniqueElements(result5)) << "Sorting approach has duplicates";
        EXPECT_TRUE(hasUniqueElements(result6)) << "Counting Sort approach has duplicates";
        
        // All results should have top k frequencies
        EXPECT_TRUE(hasTopKFrequencies(nums, result1, k)) << "Min-Heap approach frequencies incorrect";
        EXPECT_TRUE(hasTopKFrequencies(nums, result2, k)) << "QuickSelect approach frequencies incorrect";
        EXPECT_TRUE(hasTopKFrequencies(nums, result3, k)) << "Bucket Sort approach frequencies incorrect";
        EXPECT_TRUE(hasTopKFrequencies(nums, result4, k)) << "Max-Heap approach frequencies incorrect";
        EXPECT_TRUE(hasTopKFrequencies(nums, result5, k)) << "Sorting approach frequencies incorrect";
        EXPECT_TRUE(hasTopKFrequencies(nums, result6, k)) << "Counting Sort approach frequencies incorrect";
    }
};

// Basic functionality tests
TEST_F(TopKFrequentElementsTest, LeetCodeExample1) {
    // Input: nums = [1,1,1,2,2,3], k = 2
    // Output: [1,2] (1 appears 3 times, 2 appears 2 times)
    std::vector<int> nums = {1,1,1,2,2,3};
    int k = 2;
    testAllApproaches(nums, k);
}

TEST_F(TopKFrequentElementsTest, LeetCodeExample2) {
    // Input: nums = [1], k = 1
    // Output: [1]
    std::vector<int> nums = {1};
    int k = 1;
    testAllApproaches(nums, k);
}

// Edge cases
TEST_F(TopKFrequentElementsTest, SingleElementArray) {
    std::vector<int> nums = {42};
    testAllApproaches(nums, 1);
}

TEST_F(TopKFrequentElementsTest, TwoElementsSameFrequency) {
    std::vector<int> nums = {1, 2};
    testAllApproaches(nums, 1);
    testAllApproaches(nums, 2);
}

TEST_F(TopKFrequentElementsTest, AllElementsSame) {
    std::vector<int> nums = {5, 5, 5, 5, 5};
    testAllApproaches(nums, 1);
}

TEST_F(TopKFrequentElementsTest, AllElementsUnique) {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    testAllApproaches(nums, 1);
    testAllApproaches(nums, 3);
    testAllApproaches(nums, 5);
}

TEST_F(TopKFrequentElementsTest, KEqualsUniqueCount) {
    std::vector<int> nums = {1, 1, 2, 2, 3, 3};
    testAllApproaches(nums, 3); // All unique elements
}

// Frequency patterns
TEST_F(TopKFrequentElementsTest, ClearFrequencyHierarchy) {
    // Element 1 appears 4 times, 2 appears 3 times, 3 appears 2 times, 4 appears 1 time
    std::vector<int> nums = {1,1,1,1, 2,2,2, 3,3, 4};
    testAllApproaches(nums, 1); // Should be [1]
    testAllApproaches(nums, 2); // Should be [1,2]
    testAllApproaches(nums, 3); // Should be [1,2,3]
}

TEST_F(TopKFrequentElementsTest, TiedFrequencies) {
    // Multiple elements with same frequency
    std::vector<int> nums = {1,1, 2,2, 3,3, 4,4};
    testAllApproaches(nums, 2); // Any 2 elements are valid
    testAllApproaches(nums, 4); // All elements
}

TEST_F(TopKFrequentElementsTest, MajorityElement) {
    std::vector<int> nums = {1,1,1,1,1,1, 2, 3};
    testAllApproaches(nums, 1); // Should be [1]
    testAllApproaches(nums, 2); // Should include 1 and one of {2,3}
}

// Negative numbers
TEST_F(TopKFrequentElementsTest, NegativeNumbers) {
    std::vector<int> nums = {-1,-1,-1, -2,-2, 3};
    testAllApproaches(nums, 1); // Should be [-1]
    testAllApproaches(nums, 2); // Should be [-1, -2] or [-1, 3]
}

TEST_F(TopKFrequentElementsTest, MixedPositiveNegative) {
    std::vector<int> nums = {-5,-5,-5, 0,0, 10,10,10,10};
    testAllApproaches(nums, 1); // Should be [10]
    testAllApproaches(nums, 2); // Should be [10, -5]
}

TEST_F(TopKFrequentElementsTest, AllNegative) {
    std::vector<int> nums = {-10,-10, -20,-20,-20, -30};
    testAllApproaches(nums, 1); // Should be [-20]
    testAllApproaches(nums, 2); // Should be [-20] and one of {-10, -30}
}

// Zero handling
TEST_F(TopKFrequentElementsTest, WithZeros) {
    std::vector<int> nums = {0,0,0, 1,1, -1};
    testAllApproaches(nums, 1); // Should be [0]
    testAllApproaches(nums, 2); // Should be [0, 1]
}

TEST_F(TopKFrequentElementsTest, OnlyZeros) {
    std::vector<int> nums = {0,0,0,0,0};
    testAllApproaches(nums, 1); // Should be [0]
}

// Large numbers (constraint boundaries)
TEST_F(TopKFrequentElementsTest, ConstraintBoundaries) {
    std::vector<int> nums = {10000,10000, -10000,-10000,-10000, 0};
    testAllApproaches(nums, 1); // Should be [-10000]
    testAllApproaches(nums, 2); // Should be [-10000, 10000]
}

TEST_F(TopKFrequentElementsTest, MaxValues) {
    std::vector<int> nums = {10000,10000,10000, 9999,9999, -10000};
    testAllApproaches(nums, 1); // Should be [10000]
    testAllApproaches(nums, 2); // Should be [10000, 9999]
}

// Performance and scalability tests
TEST_F(TopKFrequentElementsTest, LargeArraySmallK) {
    std::vector<int> nums;
    // Create array with clear frequency pattern
    for (int i = 0; i < 100; i++) nums.push_back(1); // 100 1's
    for (int i = 0; i < 50; i++) nums.push_back(2);  // 50 2's
    for (int i = 0; i < 25; i++) nums.push_back(3);  // 25 3's
    for (int i = 0; i < 10; i++) nums.push_back(i + 10); // 10 unique elements with freq 1
    
    testAllApproaches(nums, 1); // Should be [1]
    testAllApproaches(nums, 3); // Should be [1, 2, 3]
}

TEST_F(TopKFrequentElementsTest, ManyUniqueElements) {
    std::vector<int> nums;
    for (int i = 1; i <= 100; i++) {
        for (int j = 0; j < i; j++) {
            nums.push_back(i);
        }
    }
    
    testAllApproaches(nums, 5); // Top 5 should be [100, 99, 98, 97, 96]
    testAllApproaches(nums, 10); // Top 10 most frequent
}

TEST_F(TopKFrequentElementsTest, RepeatedPatterns) {
    std::vector<int> nums;
    // Create repeated pattern: 1,2,3,1,2,3,1,2,3...
    for (int i = 0; i < 100; i++) {
        nums.push_back((i % 3) + 1);
    }
    // Add extra 1's to make it most frequent
    for (int i = 0; i < 10; i++) nums.push_back(1);
    
    testAllApproaches(nums, 1); // Should be [1]
    testAllApproaches(nums, 2); // Should be [1] and one of {2, 3}
}

// Algorithmic edge cases
TEST_F(TopKFrequentElementsTest, BucketSortEdgeCase) {
    // Test case where bucket sort shines
    std::vector<int> nums = {1,1,1,1,1, 2,2,2,2, 3,3,3, 4,4, 5};
    testAllApproaches(nums, 3); // Clear hierarchy: 1(5), 2(4), 3(3)
}

TEST_F(TopKFrequentElementsTest, QuickSelectWorstCase) {
    // Test case that could be challenging for QuickSelect
    std::vector<int> nums;
    // Create descending frequency pattern
    for (int freq = 50; freq >= 1; freq--) {
        for (int i = 0; i < freq; i++) {
            nums.push_back(51 - freq); // Element value inversely related to frequency
        }
    }
    
    testAllApproaches(nums, 5); // Top 5 most frequent
    testAllApproaches(nums, 25); // Half of unique elements
}

TEST_F(TopKFrequentElementsTest, CountingSortOptimal) {
    // Test case ideal for counting sort (small range, high frequency)
    std::vector<int> nums;
    for (int i = -5; i <= 5; i++) {
        for (int j = 0; j < (6 + i) * 10; j++) { // Varying frequencies
            nums.push_back(i);
        }
    }
    
    testAllApproaches(nums, 3); // Top 3 in small range
}

// Stress tests
TEST_F(TopKFrequentElementsTest, HighFrequencySkew) {
    std::vector<int> nums;
    nums.insert(nums.end(), 1000, 1); // 1000 1's
    nums.insert(nums.end(), 1, 2);    // 1 2
    nums.insert(nums.end(), 1, 3);    // 1 3
    
    testAllApproaches(nums, 1); // Should clearly be [1]
    testAllApproaches(nums, 2); // Should be [1] and one of {2, 3}
}

TEST_F(TopKFrequentElementsTest, UniformDistribution) {
    std::vector<int> nums;
    // Each element appears exactly 5 times
    for (int element = 1; element <= 20; element++) {
        for (int i = 0; i < 5; i++) {
            nums.push_back(element);
        }
    }
    
    testAllApproaches(nums, 5); // Any 5 elements are valid
    testAllApproaches(nums, 10); // Any 10 elements are valid
}

// Algorithm consistency tests
TEST_F(TopKFrequentElementsTest, ConsistencyCheck) {
    std::vector<std::vector<int>> testCases = {
        {1,1,1,2,2,3},
        {1},
        {1,2,3,4,5},
        {-1,-1,0,0,0,1},
        {100,-100,100,-100,0}
    };
    
    std::vector<int> kValues = {1, 2, 3};
    
    for (const auto& nums : testCases) {
        for (int k : kValues) {
            if (k <= nums.size()) {
                testAllApproaches(nums, std::min(k, (int)std::set<int>(nums.begin(), nums.end()).size()));
            }
        }
    }
}

// Performance comparison test
TEST_F(TopKFrequentElementsTest, PerformanceTest) {
    // Create large test case
    std::vector<int> nums;
    for (int i = 1; i <= 1000; i++) {
        for (int j = 0; j < (1001 - i); j++) { // Decreasing frequency
            nums.push_back(i);
        }
    }
    
    // Test different approaches (focusing on those that should be O(n))
    auto result1 = solution.topKFrequent(nums, 10);
    auto result2 = solution.topKFrequentQuickSelect(nums, 10);
    auto result3 = solution.topKFrequentBucketSort(nums, 10);
    
    // All should give same result size
    EXPECT_EQ(result1.size(), 10);
    EXPECT_EQ(result2.size(), 10);
    EXPECT_EQ(result3.size(), 10);
}

// Boundary tests
TEST_F(TopKFrequentElementsTest, MinimumConstraints) {
    // Minimum case: 1 element, k=1
    std::vector<int> nums = {-10000};
    testAllApproaches(nums, 1);
}

TEST_F(TopKFrequentElementsTest, AlmostMaxConstraints) {
    // Large array within constraints
    std::vector<int> nums;
    for (int i = 0; i < 10000; i++) {
        nums.push_back(i % 100); // 100 unique elements, each appearing 100 times
    }
    
    testAllApproaches(nums, 1);
    testAllApproaches(nums, 10);
    testAllApproaches(nums, 50);
}

}
}
}