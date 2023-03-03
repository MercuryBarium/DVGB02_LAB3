#include "sim_engine.h"
#ifndef COMMON_H
#define COMMON_H
#define TABLE_ENTRIES 4
#define INFINITY 999
const char * node_color(int me);
void initINF(int dt[TABLE_ENTRIES][TABLE_ENTRIES], int pos, int known[TABLE_ENTRIES]);
void response_doer(struct rtpkt * rcvdpkt,int me, int known_by_me[TABLE_ENTRIES]);
void advertise(int me, int k[TABLE_ENTRIES]);
#endif