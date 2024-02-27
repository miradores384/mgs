/*
mgs::html library
  Provide 'html' related functions

  Author
    Martin Scott February 2024
*/

#ifndef mgsHtml_H
#define mgsHtml_H

#include <string>


namespace mgs
{
  namespace html
  {
    std::string buildPage(std::string bodyContent, std::string pageTitle, unsigned int refreshDelaySeconds, std::string refreshTargetUrl); 
  }
}

#endif