#include "StringUtils.h"

namespace StringUtils{

std::string Slice(const std::string &str, ssize_t start, ssize_t end) noexcept{
    if (start < 0) start += str.size();
    if (end <= 0) end += str.size();
    if (start < 0) start = 0;
    if (end > static_cast<ssize_t>(str.size())) end = str.size();
    return (start < end) ? str.substr(start, end - start) : "";
}

std::string Capitalize(const std::string &str) noexcept{
    if (str.empty()) return str;
    std::string result = str;
    result[0] = std::toupper(result[0]);
    for (size_t i = 1; i < result.size(); ++i) {
        result[i] = std::tolower(result[i]);
    }
    return result;
}

std::string Upper(const std::string &str) noexcept{
    std::string result = str;
    for (char &c : result) c = std::toupper(c);
    return result;
}

std::string Lower(const std::string &str) noexcept{
    std::string result = str;
    for (char &c : result) c = std::tolower(c);
    return result;
}

std::string LStrip(const std::string &str) noexcept{
    size_t start = str.find_first_not_of(" \t\n\r");
    return (start == std::string::npos) ? "" : str.substr(start);
}

std::string RStrip(const std::string &str) noexcept{
    size_t end = str.find_last_not_of(" \t\n\r");
    return (end == std::string::npos) ? "" : str.substr(0, end + 1);
}

std::string Strip(const std::string &str) noexcept{
    return LStrip(RStrip(str));
}

std::string Center(const std::string &str, int width, char fill) noexcept{
    int padding = width - str.size();
    if (padding <= 0) return str;
    int left = padding / 2;
    int right = padding - left;
    return std::string(left, fill) + str + std::string(right, fill);
}

std::string LJust(const std::string &str, int width, char fill) noexcept{
    return str.size() >= (size_t)width ? str : str + std::string(width - str.size(), fill);
}

std::string RJust(const std::string &str, int width, char fill) noexcept{
    return str.size() >= (size_t)width ? str : std::string(width - str.size(), fill) + str;
}

std::string Replace(const std::string &str, const std::string &old, const std::string &rep) noexcept{
    if (old.empty()) return str;
    std::string result = str;
    size_t pos = 0;
    while ((pos = result.find(old, pos)) != std::string::npos) {
        result.replace(pos, old.length(), rep);
        pos += rep.length();
    }
    return result;
}

std::vector<std::string> Split(const std::string &str, const std::string &splt) noexcept{
    std::vector<std::string> tokens;
    size_t start = 0, end;
    while ((end = str.find(splt, start)) != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + splt.length();
    }
    tokens.push_back(str.substr(start));
    return tokens;
}

std::string Join(const std::string &str, const std::vector<std::string> &vect) noexcept{
    std::string result;
    for (size_t i = 0; i < vect.size(); ++i) {
        if (i > 0) result += str;
        result += vect[i];
    }
    return result;
}

std::string ExpandTabs(const std::string &str, int tabsize) noexcept{
    std::string result;
    for (char c : str) {
        if (c == '\t') {
            result.append(tabsize - result.size() % tabsize, ' ');
        } else {
            result.push_back(c);
        }
    }
    return result;
}

int EditDistance(const std::string &left, const std::string &right, bool ignorecase) noexcept{
    size_t len1 = left.size(), len2 = right.size();
    std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1));

    for (size_t i = 0; i <= len1; ++i) {
        for (size_t j = 0; j <= len2; ++j) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else {
                int cost = (ignorecase ? (tolower(left[i - 1]) != tolower(right[j - 1])) 
                                       : (left[i - 1] != right[j - 1])) ? 1 : 0;

                dp[i][j] = std::min(std::min(dp[i - 1][j] + 1,   // Deletion
                                             dp[i][j - 1] + 1),  // Insertion
                                             dp[i - 1][j - 1] + cost); // Substitution
            }
        }
    }
    return dp[len1][len2];
}

};
