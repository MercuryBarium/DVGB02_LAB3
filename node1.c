#include <stdio.h>

#include "sim_engine.h"
#include "common.h"

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table {
  int costs[TABLE_ENTRIES][TABLE_ENTRIES];
} dt1;

/* Students to write the following two routines, and maybe some others */

void printdt1(struct distance_table *dtptr) {
  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);
}

void rtinit1() {
  int me = 1;
  printf("\e[0;33mInitializing Node 1...\e[0m\n");
  int known[] = {1,0,1,INFINITY};
  initINF(dt1.costs, me, known);
  
  advertise(me, dt1.costs);
  
}

void rtupdate1(struct rtpkt *rcvdpkt) {
    /* TODO */
  int me = 1;
  if (response_doer(rcvdpkt, me, dt1.costs[me], dt1.costs))
    advertise(me, dt1.costs);
    
  printf("%s", node_color(1));
  printdt1(&dt1);
  printf("\e[0m");

}

void linkhandler1(int linkid, int newcost) {
  /* DON'T CHANGE */
}


