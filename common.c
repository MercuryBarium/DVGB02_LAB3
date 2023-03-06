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
    dt[pos][i] = known[i]; // Bidirectional
    //dt[i][pos] = known[i];
  }
}
void response_doer(struct rtpkt *rcvdpkt, int me, int known_by_me[TABLE_ENTRIES], int dt[TABLE_ENTRIES][TABLE_ENTRIES])
{
  //printf("%sNODE %d RECIEVED FROM Node %d\n", node_color(me), me, rcvdpkt->sourceid);
  for (int i = 0; i < TABLE_ENTRIES; i++)
    if (dt[rcvdpkt->sourceid][i] > rcvdpkt->mincost[i])
    {
      //printf("\tDT[%d][%d]\t<-\t%d\n", rcvdpkt->sourceid, i, rcvdpkt->mincost[i]);
      dt[rcvdpkt->sourceid][i] = rcvdpkt->mincost[i]; // Bidirectional
      //dt[i][rcvdpkt->sourceid] = rcvdpkt->mincost[i];
    }
  //printf("\e[0m");
}

void advertise(int me, int k[TABLE_ENTRIES])
{
  //printf("%s::::::::ADVERTISING::NODE::%d::::::::\n", node_color(me), me);
  for (int i = 0; i < TABLE_ENTRIES; i++)
  {
    if (i != me && k[i] != INFINITY)
    {
      struct rtpkt pkt = {
          .destid = i,
          .sourceid = me,
          .mincost = {k[0], k[1], k[2], k[3]}};
      tolayer2(pkt);
    }
  }
  //printf("::::::::ADVERTISING::DONE:::::::::::\e[0m\n");
}

void printGraph(int mtrx[TABLE_ENTRIES][TABLE_ENTRIES], int node)
{
  printf("%sNode %d\n", node_color(node), node);
  char graph[][100] = {
    "       %3d\n",
    " |0|---------|1|\n",
    "  | ¨\\___     | \n",
     "%3d   %3d\\   %2d \n",
    "  |       \\__ |\n",
    " |3|---------|2|\n",
    "       %3d\n"
  };

  int e01 = mtrx[0][1];
  if (mtrx[1][0] < e01) e01 = mtrx[1][0];
  int e03 = mtrx[0][3];
  if (mtrx[3][0] < e03) e03 = mtrx[3][0];
  int e02 = mtrx[0][2];
  if (mtrx[2][0] < e02) e02 = mtrx[2][0];
  int e12 = mtrx[1][2];
  if (mtrx[2][1] < e12) e12 = mtrx[2][1];  
  int e32 = mtrx[3][2];
  if (mtrx[2][3] < e32) e32 = mtrx[2][3];
  sprintf(graph[0], "       %3d\n", e01);
  sprintf(graph[3], "%3d   %3d\\   %2d \n", e03, e02, e12);
  sprintf(graph[6], "       %3d\n", e32);

  for (int i = 0; i<7; i++)
    printf("%s", graph[i]);

  printf("\e[0m\n");
}