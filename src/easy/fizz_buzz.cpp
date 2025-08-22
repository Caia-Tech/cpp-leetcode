#include "fizz_buzz.h"

namespace leetcode {
namespace easy {

std::vector<std::string> FizzBuzzIfElse::fizzBuzz(int n) {
    std::vector<std::string> ans;
    ans.reserve(n);
    for (int i = 1; i <= n; ++i) {
        if (i % 15 == 0) {
            ans.emplace_back("FizzBuzz");
        } else if (i % 3 == 0) {
            ans.emplace_back("Fizz");
        } else if (i % 5 == 0) {
            ans.emplace_back("Buzz");
        } else {
            ans.emplace_back(std::to_string(i));
        }
    }
    return ans;
}

std::vector<std::string> FizzBuzzConcat::fizzBuzz(int n) {
    std::vector<std::string> ans;
    ans.reserve(n);
    for (int i = 1; i <= n; ++i) {
        std::string s;
        if (i % 3 == 0) s += "Fizz";
        if (i % 5 == 0) s += "Buzz";
        if (s.empty()) s = std::to_string(i);
        ans.emplace_back(std::move(s));
    }
    return ans;
}

std::vector<std::string> FizzBuzzMap::fizzBuzz(int n) {
    std::vector<std::string> ans;
    ans.reserve(n);
    std::unordered_map<int, std::string> mp{{3, "Fizz"}, {5, "Buzz"}};
    for (int i = 1; i <= n; ++i) {
        std::string s;
        for (const auto& [div, word] : mp) {
            if (i % div == 0) s += word;
        }
        if (s.empty()) s = std::to_string(i);
        ans.emplace_back(std::move(s));
    }
    return ans;
}

std::vector<std::string> FizzBuzzSwitch::fizzBuzz(int n) {
    std::vector<std::string> ans;
    ans.reserve(n);
    for (int i = 1; i <= n; ++i) {
        switch (i % 15) {
            case 0: ans.emplace_back("FizzBuzz"); break;
            case 3: case 6: case 9: case 12: ans.emplace_back("Fizz"); break;
            case 5: case 10: ans.emplace_back("Buzz"); break;
            default: ans.emplace_back(std::to_string(i)); break;
        }
    }
    return ans;
}

std::vector<std::string> FizzBuzzPrecompute::fizzBuzz(int n) {
    static const std::array<std::string,15> cycle = {
        "1","2","Fizz","4","Buzz","Fizz","7","8","Fizz","Buzz",
        "11","Fizz","13","14","FizzBuzz"};
    std::vector<std::string> ans;
    ans.reserve(n);
    for (int i = 1; i <= n; ++i) {
        ans.emplace_back(cycle[(i-1)%15]);
    }
    return ans;
}

std::vector<std::string> FizzBuzzModuloArray::fizzBuzz(int n) {
    static const std::array<std::string,3> fizz = {"", "", "Fizz"};
    static const std::array<std::string,5> buzz = {"", "", "", "", "Buzz"};
    std::vector<std::string> ans;
    ans.reserve(n);
    for (int i = 1; i <= n; ++i) {
        std::string s = fizz[i%3] + buzz[i%5];
        if (s.empty()) s = std::to_string(i);
        ans.emplace_back(std::move(s));
    }
    return ans;
}

} // namespace easy
} // namespace leetcode

