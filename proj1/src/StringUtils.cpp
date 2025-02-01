#include "StringUtils.h"

namespace StringUtils{

std::string Slice(const std::string &str, ssize_t start, ssize_t end) noexcept{
    if (start < 0) start += str.size(); // if the index is negative, work backwards
    if (end <= 0) end += str.size(); // if the end is negative, adjust from there
    if (start < 0) start = 0; // check to make sure that the start is at 0 or positive
    if (end > static_cast<ssize_t>(str.size())) end = str.size(); // make sure the end of the string is within the length
    return (start < end) ? str.substr(start, end - start) : ""; // return my sliced string
}


std::string Capitalize(const std::string &str) noexcept{
    if (str.empty()) return str; // return if there is no string
    std::string result = str;
    result[0] = std::toupper(result[0]); // capitalize first character in the string
    for (size_t i = 1; i < result.size(); ++i) {
        result[i] = std::tolower(result[i]); // convert rest of the string to lowercase
    }
    return result;
}


std::string Upper(const std::string &str) noexcept{
    std::string result = str;
    for (char &c : result) c = std::toupper(c); //convertss each character in teh string to uppercase
    return result;
}


std::string Lower(const std::string &str) noexcept{
    std::string result = str;
    for (char &c : result) c = std::tolower(c); //conversts each character in the strin gto lowercase
    return result;
}


std::string LStrip(const std::string &str) noexcept{
    size_t start = str.find_first_not_of(" \t\n\r"); // find the first character in the string that's not whitespace
    return (start == std::string::npos) ? "" : str.substr(start); // return a substring with a new start point
}


std::string RStrip(const std::string &str) noexcept{
    size_t end = str.find_last_not_of(" \t\n\r"); // find the last character in the string that's not whitespace
    return (end == std::string::npos) ? "" : str.substr(0, end + 1); // return a substring with a new end point
}


std::string Strip(const std::string &str) noexcept{
    return LStrip(RStrip(str)); // calls both left and right strip functions
}


std::string Center(const std::string &str, int width, char fill) noexcept{
    int extra = width - str.size(); // calculate the toal extra space needed
    if (extra <= 0) return str; // if the extra space is 0 or negative, we dont need any
    int left = extra / 2; //left is extra/2
    int right = extra - left; // right is extra/2
    return std::string(left, fill) + str + std::string(right, fill); // center the string with the new extra 
}


std::string LJust(const std::string &str, int width, char fill) noexcept{
    return str.size() >= (size_t)width ? str : str + std::string(width - str.size(), fill); // add the extra space on the right
}


std::string RJust(const std::string &str, int width, char fill) noexcept{
    return str.size() >= (size_t)width ? str : std::string(width - str.size(), fill) + str; // add the extra space on teht left
}


std::string Replace(const std::string &str, const std::string &old, const std::string &rep) noexcept{
    if (old.empty()) return str; // if the string is empty, return
    std::string result = str;
    size_t pos = 0;
    while ((pos = result.find(old, pos)) != std::string::npos) { // iterate through thte string looking for the substring
        result.replace(pos, old.length(), rep); // replace the old substring with the new substring
        pos += rep.length(); //iterate to the next character
    }
    return result;
}


std::vector<std::string> Split(const std::string &str, const std::string &splt) noexcept{
    std::vector<std::string> splitsub;
    size_t start = 0, end;
    while ((end = str.find(splt, start)) != std::string::npos) { // find where we want to split the string
        splitsub.push_back(str.substr(start, end - start)); //create gap in the string 
        start = end + splt.length(); //move to the next part of the string
    }
    splitsub.push_back(str.substr(start)); // add the new string pack on 
    return splitsub;
}


std::string Join(const std::string &str, const std::vector<std::string> &vect) noexcept{
    std::string result;
    for (size_t i = 0; i < vect.size(); ++i) {
        if (i > 0) result += str; // add the string to the string
        result += vect[i]; // add the vector to the string and repeat
    }
    return result;
}


std::string ExpandTabs(const std::string &str, int tabsize) noexcept{
    std::string result;
    for (char c : str) {
        if (c == '\t') {
            result.append(tabsize - result.size() % tabsize, ' '); //find tabs in the string and replace them with tabsize spaces
        } else {
            result.push_back(c); //move the current character to the next space
        }
    }
    return result;
}

// Computes the edit distance (Levenshtein distance) between two strings
int EditDistance(const std::string &left, const std::string &right, bool ignorecase) noexcept{
    size_t len1 = left.size(), len2 = right.size();
    std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1)); // create a 2D vector for the distances

    for (size_t i = 0; i <= len1; ++i) {
        for (size_t j = 0; j <= len2; ++j) {
            if (i == 0) {
                dp[i][j] = j; // find the cost of adding the j characters
            } else if (j == 0) {
                dp[i][j] = i; //find the cost of removing the i characters
            } else {
                int cost = (ignorecase ? (tolower(left[i - 1]) != tolower(right[j - 1])) 
                                       : (left[i - 1] != right[j - 1])) ? 1 : 0;
                
                dp[i][j] = std::min(std::min(dp[i - 1][j] + 1,   // delete the current cost
                                             dp[i][j - 1] + 1),  // insert the new cost
                                             dp[i - 1][j - 1] + cost); // substitude the distance plus the cost for the strings
            }
        }
    }
    return dp[len1][len2];
}

};
