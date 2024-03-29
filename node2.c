#include <stdio.h>

#include "sim_engine.h"
#include "common.h"

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table {
  int costs[4][4];
} dt2;



/* Students to write the following two routines, and maybe some others */


void printdt2(struct distance_table *dtptr) {
  printf("                via     \n");
  printf("   D2 |    0     1    3 \n");
  printf("  ----|-----------------\n");
  printf("     0|  %3d   %3d   %3d\n",dtptr->costs[0][0],
	 dtptr->costs[0][1],dtptr->costs[0][3]);
  printf("dest 1|  %3d   %3d   %3d\n",dtptr->costs[1][0],
	 dtptr->costs[1][1],dtptr->costs[1][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][0],
	 dtptr->costs[3][1],dtptr->costs[3][3]);
}

void rtinit2() {
  /* TODO */
  int me = 2;
  printf("\e[0;34mInitializing Node 2...\e[0m\n");
  int known[] = {3,1,0,2};
  initINF(dt2.costs, me, known);

  advertise(me, dt2.costs);
}

void rtupdate2(struct rtpkt *rcvdpkt) {
  /* TODO */
  if (response_doer(rcvdpkt, 2, dt2.costs[2], dt2.costs))
    advertise(2, dt2.costs);
  
  printf("%s", node_color(2));
  printdt2(&dt2);
  printf("\e[0m");
}








