#include "valid_anagram.h"
#include <algorithm>
#include <cmath>

namespace leetcode {
namespace easy {

bool ValidAnagramSort::isAnagram(std::string s, std::string t) {
    if (s.size() != t.size()) return false;
    std::sort(s.begin(), s.end());
    std::sort(t.begin(), t.end());
    return s == t;
}

bool ValidAnagramCountArray::isAnagram(std::string s, std::string t) {
    if (s.size() != t.size()) return false;
    std::array<int, 26> counts{};
    for (char c : s) counts[c - 'a']++;
    for (char c : t) {
        if (--counts[c - 'a'] < 0) return false;
    }
    return true;
}

bool ValidAnagramHashMap::isAnagram(std::string s, std::string t) {
    if (s.size() != t.size()) return false;
    std::unordered_map<char, int> counts;
    for (char c : s) counts[c]++;
    for (char c : t) {
        if (--counts[c] < 0) return false;
    }
    return true;
}

bool ValidAnagramCountingSort::isAnagram(std::string s, std::string t) {
    if (s.size() != t.size()) return false;
    std::vector<int> countS(26), countT(26);
    for (char c : s) countS[c - 'a']++;
    for (char c : t) countT[c - 'a']++;
    return countS == countT;
}

bool ValidAnagramPrimeProduct::isAnagram(std::string s, std::string t) {
    if (s.size() != t.size()) return false;
    static const int primes[26] = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,
        43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
    long long prod1 = 1, prod2 = 1;
    for (char c : s) prod1 *= primes[c - 'a'];
    for (char c : t) prod2 *= primes[c - 'a'];
    return prod1 == prod2;
}

bool ValidAnagramSinglePass::isAnagram(std::string s, std::string t) {
    if (s.size() != t.size()) return false;
    std::array<int, 26> counts{};
    for (size_t i = 0; i < s.size(); ++i) {
        counts[s[i] - 'a']++;
        counts[t[i] - 'a']--;
    }
    for (int c : counts) if (c != 0) return false;
    return true;
}

} // namespace easy
} // namespace leetcode
