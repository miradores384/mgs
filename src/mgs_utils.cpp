/*
mgs::utils library
  General purpose functions

  Author
    Martin Scott February 2024
*/

#include <vector>
#include <string>
#include "mgs_utils.h"


namespace mgs
{
  namespace utils
  {
    // split a string into tokens using a delimiter
    std::vector<std::string> split(std::string sourceString, const char delimiter)
    {
      std::vector<std::string> result = {};
      std::string token = "";

      for(int i = 0; i < sourceString.length(); i++)
      {
        if(sourceString.at(i) == delimiter)
        {
          result.push_back(token);
          token = "";
        }
        else
        {
          token += sourceString.at(i);
        }
      }

      if (token.length() > 0)
      {
        result.push_back(token);
      }

      return result;
    }


    // return the number of digits in a integer (e.g. returns 3 for 'source = 100')
    unsigned int digitsInInteger(unsigned int source)
    {
      unsigned int digits = 0;

      do
      {
        ++digits;
        source /= 10;
      } while (source);

      return digits;
    }


    // return the integer value assigned to 'name' (e.g. returns 5 where name="someName" and source contains "someName=5")
    // throws exception when the value is not an integer
    unsigned int getIntValue(std::string name, std::vector<std::string> source)
    {
      unsigned int result = 0;

      for (std::string item : source)
      {
        std::vector<std::string> parts = split(&item[0], '=');

        if (parts.size() == 2)
        {
          if (parts[0] == name)
          {
            std::string value = parts[1];
            if (isdigit(value[0]))
            {
              result = atoi(value.c_str());
            }
            else
            {
              throw(name + " is Not an integer. Source: " + item);
            }

            break;
          }
        }
      }

      return result;
    }


    // returns a string with the 'values' inserted into the 'sourceString'
    // use {n} placeholders for each value to be inserted into the source string
    // for example: sourceString="{0} {1}!" and values[0]="Hello", values[1]="World"
    //              returns: "Hello World!""
    std::string format(std::string sourceString, std::vector<std::string> values)
    {
      size_t resultSize = sourceString.length();

      unsigned int x = 0;
      for (std::string value : values)
      {
        resultSize += value.length();           // add the size of the value
        resultSize -= digitsInInteger(x++) + 2; // subtract the size of the placeholder (e.g. {0})
      }

      std::string result = "";
      std::string placeholderNumber = "";
      bool inPlaceholder = false;

      for (unsigned int i = 0; i < sourceString.length(); i++)
      {
        if (inPlaceholder)
        {
          if (sourceString[i] == '}')
          {
            inPlaceholder = false;
            if (isdigit(placeholderNumber.c_str()[0]))
            {
              unsigned int v = atoi(placeholderNumber.c_str());
              result += values[v];
            }
          }
          else
          {
            placeholderNumber += sourceString[i];
          }
        }
        else
        {
          if (sourceString[i] != '{')
          {
            result += sourceString[i];
          }
          else
          {
            inPlaceholder = true;
            placeholderNumber = "";
          }
        }
      }

      return result;
    }
  }
}