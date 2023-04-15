#ifndef LIBMOSQUITTO_CALLBACK_H
#define LIBMOSQUITTO_CALLBACK_H

#include <mosquitto.h>
#include "common.h"

void mqtt_log_callback(struct mosquitto *mosq, void *userdata, int level, const char *str);

void mqtt_connect_callback(struct mosquitto *mosq, void *userdata, int result);

void mqtt_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message);

void mqtt_subscribe_callback(struct mosquitto *mosq, void *userdata, int mid, int qos_count, const int *granted_qos);

void mqtt_unsubscribe_callback(struct mosquitto *mosq, void *userdata, int mid);

#endif
