# Test Coverage Report

## Overall Coverage Status: ⚠️ 70/78 problems have tests (90%)

## Test Coverage by Problem

### Easy Problems (33/36 - 92% Coverage)
- 1. Two Sum — two_sum_test.cpp
- 7. Reverse Integer — reverse_integer_test.cpp
- 9. Palindrome Number — palindrome_number_test.cpp
- 13. Roman to Integer — roman_to_integer_test.cpp
- 14. Longest Common Prefix — longest_common_prefix_test.cpp
- 20. Valid Parentheses — valid_parentheses_test.cpp
- 21. Merge Two Sorted Lists — test_merge_two_sorted_lists.cpp
- 26. Remove Duplicates from Sorted Array — test_remove_duplicates_from_sorted_array.cpp
- 28. Find the Index of the First Occurrence in a String — test_find_index_of_first_occurrence.cpp
- 53. Maximum Subarray — maximum_subarray_test.cpp
- 58. Length of Last Word — test_length_of_last_word.cpp
- 66. Plus One — test_plus_one.cpp
- 67. Add Binary — test_add_binary.cpp
- 70. Climbing Stairs — climbing_stairs_test.cpp
- 94. Binary Tree Inorder Traversal — test_binary_tree_inorder_traversal.cpp
- 104. Maximum Depth of Binary Tree — test_maximum_depth_of_binary_tree.cpp
- 121. Best Time to Buy and Sell Stock — best_time_to_buy_and_sell_stock_test.cpp
- 125. Valid Palindrome — test_valid_palindrome.cpp
- 136. Single Number — test_single_number.cpp
- 169. Majority Element — test_majority_element.cpp
- 198. House Robber — test_house_robber.cpp
- 217. Contains Duplicate — test_contains_duplicate.cpp
- 242. Valid Anagram — test_valid_anagram.cpp
- 268. Missing Number — test_missing_number.cpp
- 283. Move Zeroes — test_move_zeroes.cpp
- 326. Power of Three — test_power_of_three.cpp
- 344. Reverse String — test_reverse_string.cpp
- 350. Intersection of Two Arrays II — test_intersection_of_two_arrays_ii.cpp
- 367. Valid Perfect Square — test_valid_perfect_square.cpp
- 383. Ransom Note — test_ransom_note.cpp
- 412. Fizz Buzz — test_fizz_buzz.cpp
- 704. Binary Search — test_binary_search.cpp
- 977. Squares of a Sorted Array — test_squares_of_a_sorted_array.cpp

### Medium Problems (28/33 - 85% Coverage)
- 3. Longest Substring Without Repeating Characters — longest_substring_without_repeating_test.cpp
- 5. Longest Palindromic Substring — test_longest_palindromic_substring.cpp
- 11. Container With Most Water — test_container_with_most_water.cpp
- 15. 3Sum — three_sum_test.cpp
- 31. Next Permutation — test_next_permutation.cpp
- 33. Search in Rotated Sorted Array — test_search_in_rotated_sorted_array.cpp
- 36. Valid Sudoku — test_valid_sudoku.cpp
- 39. Combination Sum — test_combination_sum.cpp
- 46. Permutations — test_permutations.cpp
- 49. Group Anagrams — test_group_anagrams.cpp
- 56. Merge Intervals — test_merge_intervals.cpp
- 62. Unique Paths — test_unique_paths.cpp
- 79. Word Search — test_word_search.cpp
- 98. Validate Binary Search Tree — test_validate_binary_search_tree.cpp
- 102. Binary Tree Level Order Traversal — test_binary_tree_level_order_traversal.cpp
- 127. Word Ladder — test_word_ladder.cpp
- 133. Clone Graph — test_clone_graph.cpp
- 139. Word Break — test_word_break.cpp
- 146. LRU Cache — test_lru_cache.cpp
- 152. Maximum Product Subarray — test_maximum_product_subarray.cpp
- 207. Course Schedule — test_course_schedule.cpp
- 215. Kth Largest Element in an Array — test_kth_largest_element.cpp
- 238. Product of Array Except Self — test_product_except_self.cpp
- 300. Longest Increasing Subsequence — test_longest_increasing_subsequence.cpp
- 322. Coin Change — test_coin_change.cpp
- 347. Top K Frequent Elements — test_top_k_frequent_elements.cpp
- 647. Palindromic Substrings — test_palindromic_substrings.cpp
- 994. Rotting Oranges — test_rotting_oranges.cpp

### Hard Problems (9/9 - 100% Coverage)
- 4. Median of Two Sorted Arrays — median_of_two_sorted_arrays_test.cpp
- 23. Merge k Sorted Lists — merge_k_sorted_lists_test.cpp
- 41. First Missing Positive — test_first_missing_positive.cpp
- 42. Trapping Rain Water — trapping_rain_water_test.cpp
- 51. N-Queens — test_n_queens.cpp
- 72. Edit Distance — test_edit_distance.cpp
- 76. Minimum Window Substring — test_minimum_window_substring.cpp
- 239. Sliding Window Maximum — test_sliding_window_maximum.cpp
- 297. Serialize and Deserialize Binary Tree — test_serialize_deserialize_binary_tree.cpp

## Missing Tests

 - Easy: remove_element, search_insert_position, sqrt_x
- Medium: add_two_numbers, four_sum, generate_parentheses, integer_to_roman, letter_combinations_of_phone_number

## Test Categories Covered

### Edge Cases ✅
- Empty inputs
- Single element arrays
- Minimum/Maximum constraints
- Null pointers (for linked lists/trees)
- Integer overflow/underflow

### Boundary Conditions ✅
- Array boundaries
- Integer limits (INT_MIN, INT_MAX)
- Problem-specific constraints
- Zero values
- Negative numbers

### Normal Cases ✅
- Typical inputs
- Various sizes
- Mixed positive/negative
- Sorted/Unsorted data
- Duplicate values

### Performance Cases ✅
- Large inputs
- Worst-case scenarios
- Best-case scenarios
- Average-case scenarios

## Running Tests

```bash
# Build the project
cd cpp-leetcode
mkdir build && cd build
cmake ..
make -j$(nproc)

# Run all tests
./leetcode_tests
```

