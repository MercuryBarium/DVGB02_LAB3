#include <string.h>
#include <stdio.h>
#include "common.h"
const static char COLORS[][8] = {"\e[0;32m", "\e[33m", "\e[0;34m", "\e[0;31m"};

const char *node_color(int me)
{
  return COLORS[me];
}

void initINF(int dt[TABLE_ENTRIES][TABLE_ENTRIES], int pos, int known[TABLE_ENTRIES])
{
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      dt[i][j] = INFINITY;

  for (int i = 0; i < 4; i++)
  {
    dt[i][i] = known[i]; // Bidirectional
  }
}
int response_doer(struct rtpkt *rcvdpkt, int me, int known_by_me[TABLE_ENTRIES], int dt[TABLE_ENTRIES][TABLE_ENTRIES])
{
  printf("%sNODE %d RECIEVED FROM Node %d\n", node_color(me), me, rcvdpkt->sourceid);
  int a = 0;
  int via = rcvdpkt->sourceid;
  for (int i = 0; i < TABLE_ENTRIES; i++)
  {
    if (dt[i][via] > dt[via][via] + rcvdpkt->mincost[i])
    {
      printf("dt[i][via]:%d > dt[via][via]:%d + rcvdpkt->mincost[i]:%d\n", dt[i][via], dt[via][via], rcvdpkt->mincost[i]);
      dt[i][via] = dt[via][via] + rcvdpkt->mincost[i];
      a = 1;
    }
  }
  printf("\e[0m");
  return a;
}

void advertise(int me, int dt[TABLE_ENTRIES][TABLE_ENTRIES])
{
  printf("%s::::::::ADVERTISING::NODE::%d::::::::\e[0m\n", node_color(me), me);
  struct rtpkt p = {
    .destid = 0,
    .sourceid = me,
    .mincost = {INFINITY,INFINITY,INFINITY,INFINITY}
  };

  for (int d = 0; d < TABLE_ENTRIES; d++)
  {
    for (int v = 0; v < TABLE_ENTRIES; v++)
    {
      if (dt[d][v] < p.mincost[d])
        p.mincost[d] = dt[d][v];
    }
  }
  for (int i = 0; i < TABLE_ENTRIES; i++)
  {
    if (i != me && dt[i][i] != INFINITY)
    {
      p.destid = i;
      tolayer2(p);
    }

  }
}