/*
mgs::wifi library
  Provide 'wifi' related functions

  Author
    Martin Scott February 2024
*/

#include <WiFi.h>
#include <string>
#include <mgs_serial.h>
#include "mgs_wifi.h"


namespace mgs
{
  namespace wifi
  {
    // connect to a Wifi network
    std::string connect(std::string ssidLocal, std::string passwordLocal)
    {
      SERIAL_PRINT(F("Connecting to "));
      SERIAL_PRINTLN((String)ssidLocal.c_str());

      WiFi.begin(ssidLocal.c_str(), passwordLocal.c_str());
      while (WiFi.status() != WL_CONNECTED) 
      {
          delay(500);
      }

      SERIAL_PRINT(F("WiFi connected. IP address: "));
      SERIAL_PRINTLN(WiFi.localIP());

      return (std::string)WiFi.localIP().toString().c_str();
    }


    // extract the URL from a HTTP Request
    // appends the POSTDATA for POST Requests
    char* getRequestURL(WiFiClient *client)
    {
      char *result = 0;

      while(client->available() && result == 0) 
      {
        String line = client->readStringUntil('\n');

        if(line.startsWith("GET /") || line.startsWith("POST /"))
        {
          line.replace(" HTTP/1.1\r", "");

          if(line.startsWith("GET /"))
          {
            line.remove(0, 5);              // remove 'GET /'
          }
          else
          {
            line.remove(0, 6);              // remove 'POST /'

            char *postData = getPostData(client);
            for(int i = 0; i < strlen(postData); i++)
            {
              line += postData[i];
            }
          }

          unsigned int len = line.length();
          result = new char[len+1];         // 1 extra for the terminating NULL
          line.toCharArray(result, len+1);
        } 
      }

      return result;
    }


    // get the POSTDATA from the request
    char* getPostData(WiFiClient *client)
    {
      char *result = 0;
      
      while(client->available())
      {
        unsigned requestLen = client->available();
        result = new char[requestLen+1];
        client->readBytesUntil('\n', result, requestLen);
        result[requestLen] = 0;
      }

      return result;
    }


    // send HTML back to the client
    void respond(WiFiClient* client, std::string bodyContent)
    {
      client->println("HTTP/1.1 200 OK");
      client->println("Content-type:text/html");
      client->println();
      client->print((String)bodyContent.c_str());
      client->println();
      client->flush();
    }
  }
}