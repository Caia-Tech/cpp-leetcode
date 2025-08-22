#include "ransom_note.h"

namespace leetcode {
namespace easy {

bool RansomNote::canConstructCountArray(const std::string& ransomNote, const std::string& magazine) {
    std::array<int, 26> counts{};
    for (char c : magazine) counts[c - 'a']++;
    for (char c : ransomNote) {
        if (--counts[c - 'a'] < 0) return false;
    }
    return true;
}

bool RansomNote::canConstructHashMap(const std::string& ransomNote, const std::string& magazine) {
    std::unordered_map<char, int> counts;
    for (char c : magazine) counts[c]++;
    for (char c : ransomNote) {
        auto it = counts.find(c);
        if (it == counts.end() || --(it->second) < 0) return false;
    }
    return true;
}

bool RansomNote::canConstructSorting(std::string ransomNote, std::string magazine) {
    std::sort(ransomNote.begin(), ransomNote.end());
    std::sort(magazine.begin(), magazine.end());
    size_t i = 0, j = 0;
    while (i < ransomNote.size() && j < magazine.size()) {
        if (ransomNote[i] == magazine[j]) {
            i++; j++;
        } else if (magazine[j] < ransomNote[i]) {
            j++;
        } else {
            return false;
        }
    }
    return i == ransomNote.size();
}

bool RansomNote::canConstructSinglePass(const std::string& ransomNote, const std::string& magazine) {
    std::array<int, 26> diff{};
    for (char c : magazine) diff[c - 'a']++;
    for (char c : ransomNote) {
        if (--diff[c - 'a'] < 0) return false;
    }
    return true;
}

bool RansomNote::canConstructMultiset(const std::string& ransomNote, const std::string& magazine) {
    std::multiset<char> letters(magazine.begin(), magazine.end());
    for (char c : ransomNote) {
        auto it = letters.find(c);
        if (it == letters.end()) return false;
        letters.erase(it);
    }
    return true;
}

bool RansomNote::canConstructMap(const std::string& ransomNote, const std::string& magazine) {
    std::map<char, int> need;
    for (char c : ransomNote) need[c]++;
    std::map<char, int> have;
    for (char c : magazine) have[c]++;
    for (const auto& [ch, cnt] : need) {
        if (have[ch] < cnt) return false;
    }
    return true;
}

} // namespace easy
} // namespace leetcode

