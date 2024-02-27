/*
mgs::esp32::camera class
  Class to provide a simple interface to a ESP32-Cam device

  Usage
    Public methods
      refreshImage    connect to the camera and retrieve an image
                      the image is stored in the 'image' property
    Public properties
      available       indicates that an image is stored in the 'image' property
      image           the bytes of the image
      name            the name of the camera

  Author
    Martin Scott February 2024
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <mgs_serial.h>
#include "mgs_esp32Cam.h"


namespace mgs
{
  namespace esp32
  {
    // default constructor
    camera::camera()
    {}


    // constructor - sets the properties for this camera
    // the camera must be configured as Soft Access Point
    // takes the wifi name, password and address for the camera
    camera::camera(const char* ssid, const char* password, const char* url)
    {
      _ssid = ssid;
      _password = password;
      _url = url;
      this->name = ssid;
      this->available = false;
    }


    // connect to the camera and retrieve an image
    // 'connectTimeout' is in milliseconds
    // 'retries' defines the number of times a connection will be retried if there is a timeout
    // 'bufferSize' defines the chunk size in bytes used for retrieving the image
    void camera::refreshImage(unsigned int connectTimeout, unsigned int bufferSize, unsigned int retries)
    {
      this->available = false;
      this->image.clear();

      retriveImage(connectTimeout, bufferSize);

      if (!this->available)
      {
        while(!this->available && retries > 0)
        {
          SERIAL_PRINTLN(F("Retrying ..."));
          retriveImage(connectTimeout, bufferSize);
          retries--;
        }
      }
    }


    // get an image and store it in the public property 'image'
    void camera::retriveImage(unsigned int connectTimeout, unsigned int bufferSize)
    {
      connect(connectTimeout);

      if (connected)
      {
        getImage(bufferSize);
        WiFi.disconnect();
      }
    }


    // connect to the camera
    void camera::connect(unsigned int connectTimeout)
    {
      connected = false;
      SERIAL_PRINTLN("Connecting to " + String(_ssid));

      WiFi.begin(_ssid, _password);

      unsigned long timeout = millis();
      while(WiFi.status() != WL_CONNECTED)
      {
        if(millis() - timeout > connectTimeout)
        {
          SERIAL_PRINTLN(F("Camera connect timeout"));
          return;
        }
      }

      SERIAL_PRINTLN(F("Camera connected"));
      connected = true;
    }


    // retrieve the image
    void camera::getImage(unsigned int bufferSize)
    {
      HTTPClient http;

      http.begin(_url);
      int httpCode = http.GET();
      int size = http.getSize();

      if (httpCode == 200 && size > 0) 
      {
        this->image.reserve(size);
        char buff[bufferSize];

        WiFiClient* stream = http.getStreamPtr();

        while(http.connected() && size > 0) 
        {
          size_t streamSize = stream->available();

          if (streamSize) 
          {
            int c = stream->readBytes(buff, ((size > sizeof(buff)) ? sizeof(buff) : size));
            this->image.insert(this->image.end(), &buff[0], &buff[c]);
            this->available = true;

            if (size > 0) 
            {
              size -= c;
            }
          }

          delay(1);
        }

        SERIAL_PRINTLN("Image received (" + String(this->image.size()) + ")");
      } 
      else 
      {
        SERIAL_PRINTLN("HTTP code: " + String(httpCode));
      }

      http.end();
    }
  }
}