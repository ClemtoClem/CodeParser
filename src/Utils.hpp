#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include <sstream>

/**
 * @brief Split a string into a vector of strings
 * @param str The string to split
 * @param delimiter The delimiter
 * @return The vector of strings
 */
std::vector<std::string> split(const std::string& str, char delimiter);

#endif // UTILS_HPP