/*
mgs::html library
  Provide 'html' related functions

  Author
    Martin Scott February 2024
*/

#include <string>
#include "mgs_html.h"


namespace mgs
{
  namespace html
  {
    // return html of a complete page.
    // for a page that refreshes - use 'refreshDelaySeconds' refresh interval and 'refreshTargetUrl' for the target page
    std::string buildPage(std::string bodyContent, std::string pageTitle, unsigned int refreshDelaySeconds, std::string refreshTargetUrl)
    {
      std::string result = "<!DOCTYPE html><html><head><title>" + pageTitle + "</title>";

      if (refreshDelaySeconds > 0)
      {
        result += "<meta http-equiv=\"refresh\" content=\"" + std::to_string(refreshDelaySeconds) + ";url=http://" + refreshTargetUrl + "/\" />";
      }

      result += "</head><body>" + bodyContent + "</body></html>";

      return result;
    }
  }
}

