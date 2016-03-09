#include "MQTTClient.h"


MQTT_Client MQTTClient::mqttClient;
MQTTClient* MQTTClient::instance = 0;

MQTTClient::MQTTClient(const char* device_id, const char* host, const char* user, const char* pass, uint32_t port, uint32_t keep_alive)
{
    MQTT_InitConnection(&MQTTClient::mqttClient, host, port, 0);

    MQTT_InitClient(&MQTTClient::mqttClient, device_id, user, pass, keep_alive, 1);

    MQTT_OnConnected(&MQTTClient::mqttClient, MQTTClient::onConnectedStatic);
    MQTT_OnDisconnected(&MQTTClient::mqttClient, MQTTClient::onDisconnectedStatic);
    MQTT_OnPublished(&MQTTClient::mqttClient, MQTTClient::onPublishedStatic);
    MQTT_OnData(&MQTTClient::mqttClient, MQTTClient::onDataStatic);

    MQTTClient::instance = this;
}

MQTTClient::MQTTClient(const char* device_id, const char* host, uint32_t port, uint32_t keep_alive)
    : MQTTClient(device_id, host, "", "", port, keep_alive)
{

}

MQTTClient::MQTTClient(String& device_id, String& host, uint32_t port, uint32_t keep_alive)
    : MQTTClient(device_id.c_str(), host.c_str(), port, keep_alive)
{

}

MQTTClient::MQTTClient(String& device_id, String& host, String& user, String& password,
    uint32_t port, uint32_t keep_alive)
    : MQTTClient(device_id.c_str(), host.c_str(), user.c_str(), password.c_str(), port, keep_alive)
{

}

void MQTTClient::onConnectedStatic(uint32_t* args)
{
    MQTTClient::instance->onConnected();
}

void MQTTClient::onDisconnectedStatic(uint32_t* args)
{
    MQTTClient::instance->onDisconnected();
}

void MQTTClient::onDataStatic(
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

    MQTTClient::instance->onData(topicStr, bufStr);
}

void MQTTClient::onPublishedStatic(uint32_t* args)
{
    MQTTClient::instance->onPublished();
}

void MQTTClient::connect()
{
    MQTT_Connect(&MQTTClient::mqttClient);
}

void MQTTClient::disconnect()
{
    MQTT_Disconnect(&MQTTClient::mqttClient);
}

bool MQTTClient::subscribe(const char* topic, uint8_t qos)
{
    return MQTT_Subscribe(&MQTTClient::mqttClient, topic, qos);
}

bool MQTTClient::subscribe(String& topic, uint8_t qos)
{
    return subscribe(topic.c_str(), qos);
}

bool MQTTClient::publish(const char* topic, const char* payload, int data_length, uint8_t qos, uint8_t retain)
{
    return MQTT_Publish(&MQTTClient::mqttClient, topic, payload, data_length, qos, retain);
}

bool MQTTClient::publish(String& topic, String& payload, uint8_t qos, uint8_t retain)
{
    return publish(topic.c_str(), payload.c_str(), payload.length(), qos, retain);
}

void MQTTClient::setLastWillTestament(const char* topic, const char* payload, uint8_t qos, uint8_t retain)
{
    MQTT_InitLWT(&MQTTClient::mqttClient, topic, payload, qos, retain);
}

void MQTTClient::setLastWillTestament(String& topic, String& payload, uint8_t qos, uint8_t retain)
{
    setLastWillTestament(topic.c_str(), payload.c_str(), qos, retain);
}

bool MQTTClient::isConnected()
{
    return (MQTTClient::mqttClient.connState >= TCP_CONNECTED);
}

void MQTTClient::onConnected()
{

}

void MQTTClient::onDisconnected()
{

}

void MQTTClient::onPublished()
{

}

void MQTTClient::onData(String& topic, String& payload)
{

}

