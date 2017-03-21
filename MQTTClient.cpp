#include "MQTTClient.h"


MQTTClient::MQTTClient(const char* device_id, const char* host, const char* user, const char* pass, uint32_t port, uint32_t keep_alive)
{
    MQTT_InitConnection(&mqttClient, (uint8_t*)host, port, 0);

    MQTT_InitClient(&mqttClient, (uint8_t*)device_id, (uint8_t*)user, (uint8_t*)pass, keep_alive, 1);

    MQTT_OnConnected(&mqttClient, MQTTClient::onConnectedStatic);
    MQTT_OnDisconnected(&mqttClient, MQTTClient::onDisconnectedStatic);
    MQTT_OnPublished(&mqttClient, MQTTClient::onPublishedStatic);
    MQTT_OnData(&mqttClient, MQTTClient::onDataStatic);

    mqttClient.user_data = (void*)this;
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
    MQTT_Client* c_client = (MQTT_Client*)args;
    MQTTClient* cpp_client = (MQTTClient*)c_client->user_data;
    cpp_client->onConnected();
}

void MQTTClient::onDisconnectedStatic(uint32_t* args)
{
    MQTT_Client* c_client = (MQTT_Client*)args;
    MQTTClient* cpp_client = (MQTTClient*)c_client->user_data;
    cpp_client->onDisconnected();
}

void MQTTClient::onDataStatic(
    uint32_t *args, const char* topic, uint32_t topic_len,
    const char *data, uint32_t data_len)
{
    MQTT_Client* c_client = (MQTT_Client*)args;
    MQTTClient* cpp_client = (MQTTClient*)c_client->user_data;

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

    cpp_client->onData(topicStr, bufStr);
}

void MQTTClient::onPublishedStatic(uint32_t* args)
{
    MQTT_Client* c_client = (MQTT_Client*)args;
    MQTTClient* cpp_client = (MQTTClient*)c_client->user_data;

    cpp_client->onPublished();
}

void MQTTClient::connect()
{
    MQTT_Connect(&mqttClient);
}

void MQTTClient::disconnect()
{
    MQTT_Disconnect(&mqttClient);
}

bool MQTTClient::subscribe(const char* topic, uint8_t qos)
{
    return MQTT_Subscribe(&mqttClient, strdup(topic), qos);
}

bool MQTTClient::subscribe(String& topic, uint8_t qos)
{
    return subscribe(topic.c_str(), qos);
}

bool MQTTClient::publish(const char* topic, const char* payload, int data_length, uint8_t qos, uint8_t retain)
{
    return MQTT_Publish(&mqttClient, topic, payload, data_length, qos, retain);
}

bool MQTTClient::publish(String& topic, String& payload, uint8_t qos, uint8_t retain)
{
    return publish(topic.c_str(), payload.c_str(), payload.length(), qos, retain);
}

void MQTTClient::setLastWillTestament(const char* topic, const char* payload, uint8_t qos, uint8_t retain)
{
    MQTT_InitLWT(&mqttClient, (uint8_t*)topic, (uint8_t*)payload, qos, retain);
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

