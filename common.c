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
    dt[i][pos] = known[i];
  }
}
int response_doer(struct rtpkt *rcvdpkt, int me, int known_by_me[TABLE_ENTRIES], int dt[TABLE_ENTRIES][TABLE_ENTRIES])
{
  int original[TABLE_ENTRIES] = {dt[me][0],dt[me][1],dt[me][2],dt[me][3]};
  int r = 0;
  printf("%sNODE %d RECIEVED FROM Node %d\e[0m\n", node_color(me), me, rcvdpkt->sourceid);
  for (int i = 0; i < TABLE_ENTRIES; i++)
  {
    if (rcvdpkt->mincost[i] != dt[rcvdpkt->sourceid][i])
      r = 1;
    dt[rcvdpkt->sourceid][i] = rcvdpkt->mincost[i]; // Bidirectional
    dt[i][rcvdpkt->sourceid] = rcvdpkt->mincost[i];
  }
  update_dt(dt, me);
  return r;
}

void advertise(int me, int k[TABLE_ENTRIES])
{
  printf("%s::::::::ADVERTISING::NODE::%d::::::::\e[0m\n", node_color(me), me);
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
      "       %3d\n"};

  int e01 = mtrx[0][1];
  if (mtrx[1][0] < e01)
    e01 = mtrx[1][0];
  int e03 = mtrx[0][3];
  if (mtrx[3][0] < e03)
    e03 = mtrx[3][0];
  int e02 = mtrx[0][2];
  if (mtrx[2][0] < e02)
    e02 = mtrx[2][0];
  int e12 = mtrx[1][2];
  if (mtrx[2][1] < e12)
    e12 = mtrx[2][1];
  int e32 = mtrx[3][2];
  if (mtrx[2][3] < e32)
    e32 = mtrx[2][3];
  sprintf(graph[0], "       %3d\n", e01);
  sprintf(graph[3], "%3d   %3d\\   %2d \n", e03, e02, e12);
  sprintf(graph[6], "       %3d\n", e32);

  for (int i = 0; i < 7; i++)
    printf("%s", graph[i]);

  printf("\e[0m\n");
}

int isDirected(int mtrx[TABLE_ENTRIES][TABLE_ENTRIES])
{
  for (int i = 0; i < TABLE_ENTRIES; i++)
    for (int j = 0; j < TABLE_ENTRIES; j++)
    {
      if (mtrx[j][i] != mtrx[i][j])
        return 1;
    }
  return 0;
}

void relax(int mtrx[TABLE_ENTRIES][TABLE_ENTRIES], int startnode)
{
  int k = startnode;
  for (int i = 0; i < TABLE_ENTRIES; i++)
    for (int j = 0; j < TABLE_ENTRIES; j++)
    {
      if (mtrx[i][k] > mtrx[i][j] + mtrx[j][k])
        mtrx[i][k] > mtrx[i][j] + mtrx[j][k];
    }
}

void makeSymmetric(int mtrx[TABLE_ENTRIES][TABLE_ENTRIES])
{
  for (int i = 0; i < TABLE_ENTRIES; i++)
    for (int j = 0; j < TABLE_ENTRIES; j++)
      if (mtrx[j][i] > mtrx[i][j])
        mtrx[j][i] = mtrx[i][j];
      else
        mtrx[i][j] = mtrx[j][i];
}

void update_dt(int mtrx[TABLE_ENTRIES][TABLE_ENTRIES], int startnode)
{
  relax(mtrx, startnode);
  makeSymmetric(mtrx);
}

