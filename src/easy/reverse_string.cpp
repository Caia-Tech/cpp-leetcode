#include "easy/reverse_string.h"

namespace leetcode {
namespace easy {

void ReverseStringTwoPointer::reverseString(std::vector<char>& s) {
    int left = 0, right = static_cast<int>(s.size()) - 1;
    while (left < right) {
        std::swap(s[left++], s[right--]);
    }
}

void ReverseStringStdReverse::reverseString(std::vector<char>& s) {
    std::reverse(s.begin(), s.end());
}

void ReverseStringStack::reverseString(std::vector<char>& s) {
    std::stack<char> st;
    for (char c : s) st.push(c);
    for (size_t i = 0; i < s.size(); ++i) {
        s[i] = st.top();
        st.pop();
    }
}

void ReverseStringRecursive::reverseString(std::vector<char>& s) {
    helper(s, 0, static_cast<int>(s.size()) - 1);
}

void ReverseStringRecursive::helper(std::vector<char>& s, int left, int right) {
    if (left >= right) return;
    std::swap(s[left], s[right]);
    helper(s, left + 1, right - 1);
}

void ReverseStringXor::reverseString(std::vector<char>& s) {
    int left = 0, right = static_cast<int>(s.size()) - 1;
    while (left < right) {
        if (s[left] != s[right]) {
            s[left] ^= s[right];
            s[right] ^= s[left];
            s[left] ^= s[right];
        }
        ++left;
        --right;
    }
}

void ReverseStringDeque::reverseString(std::vector<char>& s) {
    std::deque<char> d;
    for (char c : s) d.push_front(c);
    for (size_t i = 0; i < s.size(); ++i) {
        s[i] = d[i];
    }
}

} // namespace easy
} // namespace leetcode

