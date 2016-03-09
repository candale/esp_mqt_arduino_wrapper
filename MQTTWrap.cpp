#include "MQTTWrap.h"


MQTT_Client MQTTWrap::mqttClient;
MQTTWrap* MQTTWrap::instance = 0;

MQTTWrap::MQTTWrap(const char* device_id, const char* host, const char* user, const char* pass, uint32_t port, uint32_t keep_alive)
{
    MQTT_InitConnection(&MQTTWrap::mqttClient, host, port, 0);

    MQTT_InitClient(&MQTTWrap::mqttClient, device_id, user, pass, keep_alive, 1);

    MQTT_OnConnected(&MQTTWrap::mqttClient, MQTTWrap::onConnectedStatic);
    MQTT_OnDisconnected(&MQTTWrap::mqttClient, MQTTWrap::onDisconnectedStatic);
    MQTT_OnPublished(&MQTTWrap::mqttClient, MQTTWrap::onPublishedStatic);
    MQTT_OnData(&MQTTWrap::mqttClient, MQTTWrap::onDataStatic);

    MQTTWrap::instance = this;
}

MQTTWrap::MQTTWrap(const char* device_id, const char* host, uint32_t port, uint32_t keep_alive)
    : MQTTWrap(device_id, host, "", "", port, keep_alive)
{

}

MQTTWrap::MQTTWrap(String& device_id, String& host, uint32_t port, uint32_t keep_alive)
    : MQTTWrap(device_id.c_str(), host.c_str(), port, keep_alive)
{

}

MQTTWrap::MQTTWrap(String& device_id, String& host, String& user, String& password,
    uint32_t port, uint32_t keep_alive)
    : MQTTWrap(device_id.c_str(), host.c_str(), user.c_str(), password.c_str(), port, keep_alive)
{

}

void MQTTWrap::onConnectedStatic(uint32_t* args)
{
    MQTTWrap::instance->onConnected();
}

void MQTTWrap::onDisconnectedStatic(uint32_t* args)
{
    MQTTWrap::instance->onDisconnected();
}

void MQTTWrap::onDataStatic(
    uint32_t *args, const char* topic, uint32_t topic_len,
    const char *data, uint32_t data_len)
{
    char* topicCpy = (char*)malloc(topic_len + 1);
    memcpy(topicCpy, topic, topic_len);
    topicCpy[topic_len] = 0;
    // string it
    String topicStr(topicCpy);

    char* bufCpy = (char*)malloc(data_len + 1);
    memcpy(bufCpy, data, data_len);
    bufCpy[data_len] = 0;
    // string it
    String bufStr(bufCpy);

    free(topicCpy);
    free(bufCpy);

    MQTTWrap::instance->onData(topicStr, bufStr);
}

void MQTTWrap::onPublishedStatic(uint32_t* args)
{
    MQTTWrap::instance->onPublished();
}

void MQTTWrap::connect()
{
    MQTT_Connect(&MQTTWrap::mqttClient);
}

void MQTTWrap::disconnect()
{
    MQTT_Disconnect(&MQTTWrap::mqttClient);
}

bool MQTTWrap::subscribe(const char* topic, uint8_t qos)
{
    return MQTT_Subscribe(&MQTTWrap::mqttClient, topic, qos);
}

bool MQTTWrap::subscribe(String& topic, uint8_t qos)
{
    return subscribe(topic.c_str(), qos);
}

bool MQTTWrap::publish(const char* topic, const char* payload, int data_length, uint8_t qos, uint8_t retain)
{
    return MQTT_Publish(&MQTTWrap::mqttClient, topic, payload, data_length, qos, retain);
}

bool MQTTWrap::publish(String& topic, String& payload, uint8_t qos, uint8_t retain)
{
    return publish(topic.c_str(), payload.c_str(), payload.length(), qos, retain);
}

void MQTTWrap::setLastWillTestament(const char* topic, const char* payload, uint8_t qos, uint8_t retain)
{
    MQTT_InitLWT(&MQTTWrap::mqttClient, topic, payload, qos, retain);
}

void MQTTWrap::setLastWillTestament(String& topic, String& payload, uint8_t qos, uint8_t retain)
{
    setLastWillTestament(topic.c_str(), payload.c_str(), qos, retain);
}

bool MQTTWrap::isConnected()
{
    return (MQTTWrap::mqttClient.connState >= TCP_CONNECTED);
}

void MQTTWrap::onConnected()
{

}

void MQTTWrap::onDisconnected()
{

}

void MQTTWrap::onPublished()
{

}

void MQTTWrap::onData(String& topic, String& payload)
{

}

