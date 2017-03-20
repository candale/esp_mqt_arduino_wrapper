#ifndef MQTT_WRAPPER_HH
#define MQTT_WRAPPER_HH

#include <Arduino.h>

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

extern "C" {
    #include "mqtt/mqtt.h"
}


class MQTTClient
{
private:
    MQTT_Client mqttClient;

    static void onConnectedStatic(uint32_t* args);
    static void onDisconnectedStatic(uint32_t* args);
    static void onDataStatic(
        uint32_t *args, const char* topic, uint32_t topic_len,
        const char *data, uint32_t data_len);
    static void onPublishedStatic(uint32_t* args);

protected:
    virtual void onConnected();
    virtual void onDisconnected();
    virtual void onPublished();
    virtual void onData(String& topic, String& payload);

public:
    MQTTClient(const char* device_id, const char* host, const char* user,
             const char* pass, uint32_t port, uint32_t keep_alive);
    MQTTClient(String& device_id, String& host, String& user, String& password,
             uint32_t port, uint32_t keep_alive);
    MQTTClient(const char* device_id, const char* host, uint32_t port, uint32_t keep_alive);
    MQTTClient(String& device_id, String& host, uint32_t port, uint32_t keep_alive);

    void connect();
    void disconnect();

    void setLastWillTestament(const char* topic, const char* payload, uint8_t will_qos, uint8_t will_retain);
    void setLastWillTestament(String& topic, String& payload, uint8_t qill_qos, uint8_t will_retain);

    bool subscribe(const char* topic, uint8_t qos);
    bool subscribe(String& topic, uint8_t qos);

    bool publish(const char* topic, const char* data, int data_length, uint8_t qos, uint8_t retain);
    bool publish(String& topic, String& payload, uint8_t qos, uint8_t retain);

    bool isConnected();
};

#endif
