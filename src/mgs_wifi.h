/*
mgs::wifi library
  Provide 'wifi' related functions

  Author
    Martin Scott February 2024
*/

#ifndef mgsWifi_h
#define mgsWifi_h

#include <string>
#include <WiFi.h>


namespace mgs
{
  namespace wifi
  {
      std::string connect(std::string ssidLocal, std::string passwordLocal);
      char* getRequestURL(WiFiClient *client);
      char* getPostData(WiFiClient *client);
      void respond(WiFiClient* client, std::string bodyContent);
  }
}

#endif