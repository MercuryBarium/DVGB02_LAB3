#include <stdio.h>

#include "sim_engine.h"
#include "common.h"

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table {
  int costs[4][4];
} dt3;



/* Students to write the following two routines, and maybe some others */

void rtinit3() {
  /* TODO */
  int me = 3;
  printf("%sInitializing Node 3...\e[0m\n", node_color(me));
  int known[TABLE_ENTRIES] = {3,INFINITY,2,0};
  initINF(dt3.costs, me, known);

  advertise(me , known);
}


void rtupdate3(struct rtpkt *rcvdpkt) {
  /* TODO */
  response_doer(rcvdpkt, 3, dt3.costs[3], dt3.costs);
}

void printdt3(struct distance_table *dtptr) {
  printf("             via     \n");
  printf("   D3 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 1|  %3d   %3d\n",dtptr->costs[1][0], dtptr->costs[1][2]);
  printf("     2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
}







