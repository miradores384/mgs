/*
mgs::utils library
  General purpose functions

  Author
    Martin Scott February 2024
*/

#ifndef mgsUtils_h
#define mgsUtils_h

#include <vector>
#include <string>


namespace mgs
{
  namespace utils
  {
    std::vector<std::string> split(std::string sourceString, const char delimiter);
    unsigned int digitsInInteger(unsigned int i);
    unsigned int getIntValue(std::string name, std::vector<std::string> source);
    std::string format(std::string sourceString, std::vector<std::string> values);
  }
}

#endif