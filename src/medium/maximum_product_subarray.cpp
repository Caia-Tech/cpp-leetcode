#include "maximum_product_subarray.h"

namespace leetcode {
namespace medium {

int MaximumProductSubarray::maxProductDP(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    
    int maxProduct = nums[0];
    int maxHere = nums[0];  // Maximum product ending at current position
    int minHere = nums[0];  // Minimum product ending at current position
    
    for (int i = 1; i < nums.size(); ++i) {
        // Store current values before updating (since we need both for calculation)
        int tempMax = maxHere;
        
        // Current element can either:
        // 1. Extend the previous maximum product
        // 2. Extend the previous minimum product (if current is negative)
        // 3. Start a new subarray from current element
        maxHere = std::max({nums[i], maxHere * nums[i], minHere * nums[i]});
        minHere = std::min({nums[i], tempMax * nums[i], minHere * nums[i]});
        
        // Update global maximum
        maxProduct = std::max(maxProduct, maxHere);
    }
    
    return maxProduct;
}

int MaximumProductSubarray::maxProductBruteForce(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    
    int maxProduct = nums[0];
    
    // Check all possible subarrays
    for (int i = 0; i < nums.size(); ++i) {
        int currentProduct = 1;
        
        for (int j = i; j < nums.size(); ++j) {
            currentProduct *= nums[j];
            maxProduct = std::max(maxProduct, currentProduct);
        }
    }
    
    return maxProduct;
}

int MaximumProductSubarray::maxProductTwoPass(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    
    int n = nums.size();
    int maxProduct = nums[0];
    
    // Left to right pass
    int product = 1;
    for (int i = 0; i < n; ++i) {
        product *= nums[i];
        maxProduct = std::max(maxProduct, product);
        
        // Reset at zero (zero breaks the product chain)
        if (product == 0) {
            product = 1;
        }
    }
    
    // Right to left pass
    product = 1;
    for (int i = n - 1; i >= 0; --i) {
        product *= nums[i];
        maxProduct = std::max(maxProduct, product);
        
        // Reset at zero
        if (product == 0) {
            product = 1;
        }
    }
    
    return maxProduct;
}

int MaximumProductSubarray::maxProductKadane(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    
    int maxProduct = nums[0];
    int maxEndingHere = nums[0];
    int minEndingHere = nums[0];
    
    for (int i = 1; i < nums.size(); ++i) {
        // When we encounter a negative number, max and min swap roles
        if (nums[i] < 0) {
            std::swap(maxEndingHere, minEndingHere);
        }
        
        // Decide whether to extend current subarray or start new
        maxEndingHere = std::max(nums[i], maxEndingHere * nums[i]);
        minEndingHere = std::min(nums[i], minEndingHere * nums[i]);
        
        // Update global maximum
        maxProduct = std::max(maxProduct, maxEndingHere);
    }
    
    return maxProduct;
}

int MaximumProductSubarray::maxProductPrefixSuffix(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    
    int n = nums.size();
    int maxProduct = INT_MIN;
    
    // Calculate prefix products
    int prefixProduct = 1;
    for (int i = 0; i < n; ++i) {
        prefixProduct *= nums[i];
        maxProduct = std::max(maxProduct, prefixProduct);
        
        // Reset prefix at zero
        if (prefixProduct == 0) {
            prefixProduct = 1;
        }
    }
    
    // Calculate suffix products
    int suffixProduct = 1;
    for (int i = n - 1; i >= 0; --i) {
        suffixProduct *= nums[i];
        maxProduct = std::max(maxProduct, suffixProduct);
        
        // Reset suffix at zero
        if (suffixProduct == 0) {
            suffixProduct = 1;
        }
    }
    
    return maxProduct;
}

int MaximumProductSubarray::maxProductDivideConquer(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    
    return maxProductDCHelper(nums, 0, nums.size() - 1);
}

int MaximumProductSubarray::maxProductDCHelper(const std::vector<int>& nums, int start, int end) {
    // Base case: single element
    if (start == end) {
        return nums[start];
    }
    
    // Check if segment contains zero
    if (hasZero(nums, start, end)) {
        int zeroIndex = findZeroIndex(nums, start, end);
        int maxProduct = 0; // Zero itself
        
        // Recursively check left segment (if exists)
        if (zeroIndex > start) {
            maxProduct = std::max(maxProduct, maxProductDCHelper(nums, start, zeroIndex - 1));
        }
        
        // Recursively check right segment (if exists)
        if (zeroIndex < end) {
            maxProduct = std::max(maxProduct, maxProductDCHelper(nums, zeroIndex + 1, end));
        }
        
        return maxProduct;
    }
    
    // No zeros in segment, find maximum product
    return maxProductInSegment(nums, start, end);
}

int MaximumProductSubarray::maxProductInSegment(const std::vector<int>& nums, int start, int end) {
    // Segment without zeros
    int totalProduct = 1;
    int negativeCount = 0;
    int firstNegativeIndex = -1;
    int lastNegativeIndex = -1;
    
    // Calculate total product and count negatives
    for (int i = start; i <= end; ++i) {
        totalProduct *= nums[i];
        if (nums[i] < 0) {
            if (firstNegativeIndex == -1) {
                firstNegativeIndex = i;
            }
            lastNegativeIndex = i;
            negativeCount++;
        }
    }
    
    // If even number of negatives, entire segment is optimal
    if (negativeCount % 2 == 0) {
        return totalProduct;
    }
    
    // Odd number of negatives: try removing first or last negative
    int maxProduct = INT_MIN;
    
    // Option 1: Remove from first negative to end
    if (firstNegativeIndex > start) {
        int product = 1;
        for (int i = start; i < firstNegativeIndex; ++i) {
            product *= nums[i];
        }
        maxProduct = std::max(maxProduct, product);
    }
    
    // Option 2: Remove from start to last negative
    if (lastNegativeIndex < end) {
        int product = 1;
        for (int i = lastNegativeIndex + 1; i <= end; ++i) {
            product *= nums[i];
        }
        maxProduct = std::max(maxProduct, product);
    }
    
    // Also consider single elements if segment is small
    for (int i = start; i <= end; ++i) {
        maxProduct = std::max(maxProduct, nums[i]);
    }
    
    return maxProduct;
}

bool MaximumProductSubarray::hasZero(const std::vector<int>& nums, int start, int end) {
    for (int i = start; i <= end; ++i) {
        if (nums[i] == 0) {
            return true;
        }
    }
    return false;
}

int MaximumProductSubarray::findZeroIndex(const std::vector<int>& nums, int start, int end) {
    for (int i = start; i <= end; ++i) {
        if (nums[i] == 0) {
            return i;
        }
    }
    return -1; // Should not reach here if hasZero returned true
}

}
}