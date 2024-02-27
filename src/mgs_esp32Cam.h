/*
mgs::esp32::camera class
  Class to provide a simple interface to a ESP32-Cam device

  Author
    Martin Scott February 2024
*/

#ifndef mgsEsp32cam_H
#define mgsEsp32cam_H

#include <vector>
#include <WiFi.h>


namespace mgs
{
  namespace esp32
  {
    class camera
    {
      public:
        camera();
        camera(const char* ssid, const char* password, const char* url);
        void refreshImage(unsigned int connectTimeout, unsigned int bufferSize, unsigned int retries);

        bool available;
        std::vector<char> image;
        const char *name;


      private:
        
        void connect(unsigned int connectTimeout);
        void getImage(unsigned int bufferSize);
        void readResponse(WiFiClient *client);
        void retriveImage(unsigned int connectTimeout, unsigned int bufferSize);

        const char* _ssid;
        const char* _password;
        const char* _url;
        bool connected;
    };
  }
}

#endif