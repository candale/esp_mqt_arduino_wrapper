# ESP8266 MQTT Library Arduino Wrapper (over Tuanpmt's)

Simple class wrapper over esp_mqtt (https://github.com/tuanpmt/esp_mqtt). I created this in order to make use of the excellent library written by tuanpmt. The current libraries, like PubSubClient, do not support QoS level higher than 0 so this should be a bit better, if it works properly.

**Extensive testing has not yet been done.**

Limitations:

- cannot change to secure connection
- cannot change MQTT version

## Usage

In order to use it, you need to create another class that derives from MQTTClient and override the callbacks that you need:

- onConnected
- onDisconnected
- onPublished
- onData

### Example

```c++
#include <MQTTClient.h>
#include <ESP8266WiFi.h>

const char* ssid = "ssid";
const char* pass = "pass";

class MyClient: public MQTTClient
{
  using MQTTClient::MQTTClient;

  void onData(String& topic, String& payload) {
    Serial.println(topic);
    Serial.println(payload);
    Serial.println();
  }

  void onConnected() {
    subscribe("#", 1);
  }
};

MyClient* client;

void setup() {
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(ssid, pass);
  while (WiFi.waitForConnectResult() != WL_CONNECTED);
  Serial.println("Connected to wifi");
  
  client = new MyClient("client-id", "host", "user", "pass", 1883, 60);
  Serial.println("Connecting ...");
  client->connect();
}

void loop() {
}
```
