#include <string.h>
#include <stdio.h>
#include "common.h"
const static char COLORS[][8] = {"\e[0;32m", "\e[33m", "\e[0;34m", "\e[0;31m"};

const char * node_color(int me)
{
  return COLORS[me];
}

void initINF(int dt[TABLE_ENTRIES][TABLE_ENTRIES], int pos, int known[TABLE_ENTRIES])
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            dt[i][j] = INFINITY;

    for (int i = 0; i < 4; i++)
        dt[pos][i] = known[i];
}
void response_doer(struct rtpkt * rcvdpkt,int me, int known_by_me[TABLE_ENTRIES], int dt[TABLE_ENTRIES][TABLE_ENTRIES])
{
  printf("%sNODE %d RECIEVED FROM Node %d\n", node_color(me), me, rcvdpkt->sourceid);
  for (int i = 0; i < TABLE_ENTRIES; i++)
    if (dt[rcvdpkt->sourceid][i] > rcvdpkt->mincost[i])
    {
      printf("\tDT[%d][%d]\t<-\t%d\n", rcvdpkt->sourceid, i, rcvdpkt->mincost[i]);
      dt[rcvdpkt->sourceid][i] = rcvdpkt->mincost[i];
    }
  printf("\e[0m");


}

void advertise(int me, int k[TABLE_ENTRIES])
{
  printf("%s::::::::ADVERTISING::NODE::%d::::::::\n", node_color(me), me);
  for (int i = 0; i<TABLE_ENTRIES; i++)  
  {
    if (i != me && k[i] != INFINITY)
    {
      struct rtpkt pkt = {
        .destid = i,
        .sourceid = me,
        .mincost = {k[0],k[1],k[2],k[3]}
      };
      tolayer2(pkt);
    }
  }
  printf("::::::::ADVERTISING::DONE:::::::::::\e[0m\n");
}