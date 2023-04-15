#ifndef COMMMON_H
#define COMMMON_H

#include <stdbool.h>
#include <syslog.h>

#define DEFAULT_KEEPALIVE 60
#define DEFAULT_QOS 0

#define LOG(prio, fmt, args...) syslog(prio,fmt " (%s@%s:%d) ", ##args, __FILE__, __FUNCTION__, __LINE__)

#endif
