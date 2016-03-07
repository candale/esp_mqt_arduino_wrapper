# esp_mqt_arduino_wrapper

Simple class wrapper over esp_mqtt (https://github.com/tuanpmt/esp_mqtt). I created this to be able to use the MQTT library with method callbacks.
In order to make it work, some small changes were brought to the original library, like changing type names and paramter types.

##Usage##
In order to use it, you need to create another class that derives from MQTTWrap and override the calbacks that you need:
- onConnected
- onDisconnected
- onPublished
- onData

#####NOTE#####
Currently this wrapper works with only one client.
