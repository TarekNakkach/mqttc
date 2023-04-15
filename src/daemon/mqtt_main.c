#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>

#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "common.h"
#include "libmosquitto_callback.h"

int main(int argc, char *argv[])
{
    int args;
    char *host = NULL;
    int port, keepalive, qos;
    bool clean_session;
    while ((args = getopt(argc, argv, "hpaqc:")) != -1) {
        switch (args)
        {
            case 'h':
                host = optarg;
                break;
            case 'p':
                port = optarg;
                break;
            case 'a':
                keepalive = optarg;
                break;
            case 'q':
                qos = optarg;
                break;
            case 'c':
                clean_session = optarg;
                break;
        }
    }

    openlog(argv[0], LOG_CONS|LOG_PID, LOG_DAEMON);
    setlogmask(LOG_UPTO(LOG_ERR));
   
    mosquitto_lib_init();

    struct mosquitto *mosq = NULL;
    mosq = mosquitto_new(argv[0], clean_session, NULL);
    if (!mosq) {
        LOG(LOG_ERR, "######### Failed to create mosquitto instance");
        goto out;
    }

    mosquitto_log_callback_set(mosq, mqtt_log_callback);
    mosquitto_connect_callback_set(mosq, mqtt_connect_callback);
    mosquitto_message_callback_set(mosq, mqtt_message_callback);
    mosquitto_subscribe_callback_set(mosq, mqtt_subscribe_callback);
    mosquitto_unsubscribe_callback_set(mosq, mqtt_unsubscribe_callback);

    LOG(LOG_NOTICE, "######### Start connection to (%s) : port (%d)", host, port);

    if (mosquitto_connect(mosq, host, port, keepalive)) {
        LOG(LOG_ERR, "######### %s", strerror(errno));
        goto out;
    }

    mosquitto_loop_forever(mosq, -1, 1);

    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
out:
    closelog();

    return EXIT_SUCCESS;
}
