# mgs libraries
libraries for use in Arduino projects

|Library|Description|
| :--- | :--- |
| mgs::utils | General purpose functions |
| mgs::wifi | Wifi related functions |
| mgs::html | HTML related functions |
| mgs::esp32::camera | Class providing interface to ESP32-Cam devices |
| mgs::serial | Enable/disable serial (debug) output |


---

## mgs::utils
**General purpose functions**

`split`
<br>_split a string into tokens using a delimiter_
	
```cpp
std::vector<std::string> split(std::string sourceString, const char delimiter);
```


`digitsInInteger`
<br>_return the number of digits in a integer (e.g. returns 3 for 'source = 100')_
		
```cpp
unsigned int digitsInInteger(unsigned int i);
```


`getIntValue`
<br>_return the integer value assigned to 'name' (e.g. returns 5 where name="someName"<br> 
and source contains "someName=5"). throws exception when the value is not an integer_
		
```cpp
unsigned int getIntValue(std::string name, std::vector<std::string> source);
```


`format`
<br>_returns a string with the 'values' inserted into the 'sourceString'. use {n} <br>
placeholders for each value to be inserted into the source string. for example: <br>
sourceString="{0} {1}!" and values[0]="Hello", values[1]="World" - returns: "Hello World!"_

```cpp
std::string format(std::string sourceString, std::vector<std::string> values);
```

---
## mgs::wifi
**Wifi related functions**

`connect`
<br>_connect to a Wifi network_

```cpp
std::string connect(std::string ssidLocal, std::string passwordLocal);
```


`getRequestURL`
<br>_extract the URL from a HTTP Request. appends the POSTDATA for POST Requests._

```cpp
char* getRequestURL(WiFiClient *client);
```


`getPostData`
<br>_get the POSTDATA from the request_

```cpp		
char* getPostData(WiFiClient *client);
```


`respond`
<br>_send HTML back to the client_
		
```cpp
void respond(WiFiClient* client, std::string bodyContent);
```

---
## mgs::html
**HTML related functions**

`buildPage`
<br>_return html of a complete page. for a page that refreshes - use <br>
'refreshDelaySeconds' refresh interval and 'refreshTargetUrl' for the target page_

```cpp
std::string buildPage(std::string bodyContent, std::string pageTitle, unsigned int refreshDelaySeconds, std::string refreshTargetUrl);
```

---
## mgs::esp32::camera
**Class to provide a simple interface to a ESP32-Cam device**

`camera`
<br>_constructor - sets the properties for this camera. the camera must <br>
be configured as Soft Access Point. takes the wifi name, password and address for the camera._

```cpp
camera(const char* ssid, const char* password, const char* url);
```


`refreshImage`
<br>_connect to the camera and retrieve an image. 'connectTimeout' is in milliseconds. <br>
'retries' defines the number of times a connection will be retried if there is a timeout. <br>
'bufferSize' defines the chunk size in bytes used for retrieving the image._

```cpp
void refreshImage(unsigned int connectTimeout, unsigned int bufferSize, unsigned int retries);
```


`available`
<br>_indicates that an image is stored in the 'image' property_

```cpp
bool available;
```


`image`
<br>_the bytes of the image_

```cpp
std::vector<char> image;
```


`name`
<br>_the name of the camera_

```cpp
const char *name;
```

---
## mgs::serial
**Provides a method to enable/disable serial (debug) output**

`Usage`
<br>_Declare 'serialEnabled' in the application and set to 'true' <br>
for normal output or 'false' to disable the serial output._

`Replace all 'serial' statements`
<br>_in the application as follows._
      
```cpp      
      Serial.begin(x);      SERIAL_BEGIN(x);
      Serial.print(x);      SERIAL_PRINT(x);
      Serial.println(x);    SERIAL_PRINTLN(x);
      Serial.print(x,y);    SERIAL_PRINT2(x,y);
      Serial.println(x,y);  SERIAL_PRINTLN2(x,y);
```
---