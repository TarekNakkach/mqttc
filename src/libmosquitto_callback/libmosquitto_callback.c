#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>

#include "libmosquitto_callback.h"

void mqtt_log_callback(struct mosquitto *mosq, void *userdata, int level, const char *str)
{
    LOG(LOG_INFO, "######### Log : %s", str);
}

void mqtt_connect_callback(struct mosquitto *mosq, void *userdata, int result)
{
    if (!result) {
		LOG(LOG_ERR, "######### Connect Succes");
    } else {
        LOG(LOG_ERR, "######### Connect failed");
    }
}

void mqtt_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
    if (message->payloadlen)
    {
        LOG(LOG_INFO, "######### Recived Message (topic : '%s'  payload : '%s')", message->topic, (char*) message->payload);
    }
    fflush(stdout);
}

void mqtt_subscribe_callback(struct mosquitto *mosq, void *userdata, int mid, int qos_count, const int *granted_qos)
{
    LOG(LOG_INFO, "######### Subscribed (mid: %d): %d", mid, granted_qos[0]);
    for (int i = 1; i < qos_count; i++) {
        LOG(LOG_INFO, "%d", granted_qos[i]);
    }
}

void mqtt_unsubscribe_callback(struct mosquitto *mosq, void *userdata, int mid)
{
    LOG(LOG_INFO, "######### Unsubscribed (mid: %d)", mid);
}
