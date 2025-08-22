cmake_minimum_required(VERSION 3.16)
project(cpp_leetcode)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

find_package(benchmark)

add_library(leetcode_lib
    src/utils/data_structures.cpp
    src/easy/add_binary.cpp
    src/easy/best_time_to_buy_and_sell_stock.cpp
    src/easy/binary_search.cpp
    src/easy/binary_tree_inorder_traversal.cpp
    src/easy/climbing_stairs.cpp
    src/easy/contains_duplicate.cpp
    src/easy/find_index_of_first_occurrence.cpp
    src/easy/fizz_buzz.cpp
    src/easy/house_robber.cpp
    src/easy/intersection_of_two_arrays_ii.cpp
    src/easy/length_of_last_word.cpp
    src/easy/longest_common_prefix.cpp
    src/easy/majority_element.cpp
    src/easy/maximum_subarray.cpp
    src/easy/merge_two_sorted_lists.cpp
    src/easy/missing_number.cpp
    src/easy/move_zeroes.cpp
    src/easy/maximum_depth_of_binary_tree.cpp
    src/easy/palindrome_number.cpp
    src/easy/plus_one.cpp
    src/easy/power_of_three.cpp
    src/easy/ransom_note.cpp
    src/easy/remove_duplicates_from_sorted_array.cpp
    src/easy/remove_element.cpp
    src/easy/reverse_integer.cpp
    src/easy/reverse_string.cpp
    src/easy/roman_to_integer.cpp
    src/easy/search_insert_position.cpp
    src/easy/single_number.cpp
    src/easy/sqrt_x.cpp
    src/easy/squares_of_a_sorted_array.cpp
    src/easy/two_sum.cpp
    src/easy/valid_anagram.cpp
    src/easy/valid_palindrome.cpp
    src/easy/valid_parentheses.cpp
    src/easy/valid_perfect_square.cpp
    src/medium/add_two_numbers.cpp
    src/medium/binary_tree_level_order_traversal.cpp
    src/medium/clone_graph.cpp
    src/medium/coin_change.cpp
    src/medium/combination_sum.cpp
    src/medium/container_with_most_water.cpp
    src/medium/course_schedule.cpp
    src/medium/four_sum.cpp
    src/medium/generate_parentheses.cpp
    src/medium/group_anagrams.cpp
    src/medium/integer_to_roman.cpp
    src/medium/kth_largest_element.cpp
    src/medium/letter_combinations_of_phone_number.cpp
    src/medium/longest_increasing_subsequence.cpp
    src/medium/longest_palindromic_substring.cpp
    src/medium/longest_substring_without_repeating.cpp
    src/medium/lru_cache.cpp
    src/medium/maximum_product_subarray.cpp
    src/medium/merge_intervals.cpp
    src/medium/next_permutation.cpp
    src/medium/palindromic_substrings.cpp
    src/medium/permutations.cpp
    src/medium/product_except_self.cpp
    src/medium/rotting_oranges.cpp
    src/medium/search_in_rotated_sorted_array.cpp
    src/medium/three_sum.cpp
    src/medium/top_k_frequent_elements.cpp
    src/medium/unique_paths.cpp
    src/medium/valid_sudoku.cpp
    src/medium/validate_binary_search_tree.cpp
    src/medium/word_break.cpp
    src/medium/word_ladder.cpp
    src/medium/word_search.cpp
    src/hard/edit_distance.cpp
    src/hard/first_missing_positive.cpp
    src/hard/median_of_two_sorted_arrays.cpp
    src/hard/merge_k_sorted_lists.cpp
    src/hard/minimum_window_substring.cpp
    src/hard/n_queens.cpp
    src/hard/serialize_deserialize_binary_tree.cpp
    src/hard/sliding_window_maximum.cpp
    src/hard/trapping_rain_water.cpp
)

target_include_directories(leetcode_lib PUBLIC src)

add_executable(leetcode_tests
        tests/easy/best_time_to_buy_and_sell_stock_test.cpp
        tests/easy/climbing_stairs_test.cpp
        tests/easy/longest_common_prefix_test.cpp
        tests/easy/maximum_subarray_test.cpp
        tests/easy/palindrome_number_test.cpp
        tests/easy/reverse_integer_test.cpp
        tests/easy/test_reverse_string.cpp
        tests/easy/roman_to_integer_test.cpp
        tests/easy/test_binary_tree_inorder_traversal.cpp
        tests/easy/test_contains_duplicate.cpp
        tests/easy/test_fizz_buzz.cpp
        tests/easy/test_house_robber.cpp
        tests/easy/test_majority_element.cpp
        tests/easy/test_merge_two_sorted_lists.cpp
        tests/easy/test_binary_search.cpp
        tests/easy/test_maximum_depth_of_binary_tree.cpp
        tests/easy/test_add_binary.cpp
        tests/easy/test_find_index_of_first_occurrence.cpp
        tests/easy/test_length_of_last_word.cpp
        tests/easy/test_plus_one.cpp
        tests/easy/test_squares_of_a_sorted_array.cpp
        tests/easy/test_remove_duplicates_from_sorted_array.cpp
        tests/easy/test_missing_number.cpp
        tests/easy/test_move_zeroes.cpp
        tests/easy/test_single_number.cpp
        tests/easy/test_valid_anagram.cpp
        tests/easy/test_valid_palindrome.cpp
        tests/easy/test_ransom_note.cpp
        tests/easy/test_intersection_of_two_arrays_ii.cpp
        tests/easy/test_valid_perfect_square.cpp
        tests/easy/test_power_of_three.cpp
        tests/easy/two_sum_test.cpp
        tests/easy/valid_parentheses_test.cpp
        tests/hard/median_of_two_sorted_arrays_test.cpp
        tests/hard/merge_k_sorted_lists_test.cpp
        tests/hard/test_edit_distance.cpp
        tests/hard/test_first_missing_positive.cpp
        tests/hard/test_minimum_window_substring.cpp
        tests/hard/test_n_queens.cpp
        tests/hard/test_serialize_deserialize_binary_tree.cpp
        tests/hard/test_sliding_window_maximum.cpp
        tests/hard/trapping_rain_water_test.cpp
        tests/medium/longest_substring_without_repeating_test.cpp
        tests/medium/test_binary_tree_level_order_traversal.cpp
        tests/medium/test_clone_graph.cpp
        tests/medium/test_coin_change.cpp
        tests/medium/test_combination_sum.cpp
        tests/medium/test_container_with_most_water.cpp
        tests/medium/test_course_schedule.cpp
        tests/medium/test_group_anagrams.cpp
        tests/medium/test_kth_largest_element.cpp
        tests/medium/test_longest_increasing_subsequence.cpp
        tests/medium/test_longest_palindromic_substring.cpp
        tests/medium/test_lru_cache.cpp
        tests/medium/test_maximum_product_subarray.cpp
        tests/medium/test_merge_intervals.cpp
        tests/medium/test_next_permutation.cpp
        tests/medium/test_palindromic_substrings.cpp
        tests/medium/test_permutations.cpp
        tests/medium/test_product_except_self.cpp
        tests/medium/test_rotting_oranges.cpp
        tests/medium/test_search_in_rotated_sorted_array.cpp
        tests/medium/test_top_k_frequent_elements.cpp
        tests/medium/test_unique_paths.cpp
        tests/medium/test_valid_sudoku.cpp
        tests/medium/test_validate_binary_search_tree.cpp
        tests/medium/test_word_break.cpp
        tests/medium/test_word_ladder.cpp
        tests/medium/test_word_search.cpp
        tests/medium/three_sum_test.cpp
    )
target_link_libraries(leetcode_tests PRIVATE leetcode_lib GTest::gtest_main pthread)
enable_testing()
add_test(NAME leetcode_unit_tests COMMAND leetcode_tests)

if(benchmark_FOUND)
    add_executable(leetcode_benchmarks benchmarks/benchmark_main.cpp)
    target_link_libraries(leetcode_benchmarks PRIVATE leetcode_lib benchmark::benchmark pthread)
else()
    message(WARNING "Google Benchmark not found. Benchmarks will not be built.")
endif()
