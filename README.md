# Tuanmpt ESP8266 MQTT Library Arduino Wrapper

Simple class wrapper over esp_mqtt (https://github.com/tuanpmt/esp_mqtt). I created this in order to make use of the excellent library written by tuanmpt. The current libraries, like PubSubClient, do not support QoS level higher than 0 so this should be a bit better, if it works properly.

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
