#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

namespace leetcode {
namespace utils {

template<typename T>
bool vectorsEqual(const std::vector<T>& v1, const std::vector<T>& v2) {
    if (v1.size() != v2.size()) return false;
    return std::equal(v1.begin(), v1.end(), v2.begin());
}

template<typename T>
bool vectorsEqualUnordered(std::vector<T> v1, std::vector<T> v2) {
    if (v1.size() != v2.size()) return false;
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    return v1 == v2;
}

template<typename T>
std::string vectorToString(const std::vector<T>& vec) {
    std::stringstream ss;
    ss << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        ss << vec[i];
        if (i < vec.size() - 1) ss << ", ";
    }
    ss << "]";
    return ss.str();
}

template<typename T>
bool contains2DVector(const std::vector<std::vector<T>>& matrix, const std::vector<T>& target) {
    for (const auto& row : matrix) {
        if (vectorsEqual(row, target)) return true;
    }
    return false;
}

}
}