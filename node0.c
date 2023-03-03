#include <stdio.h>

#include "sim_engine.h"
#include "common.h"

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table {
  int costs[TABLE_ENTRIES][TABLE_ENTRIES];
} dt0;

int me_0 = 0;

/* Students to write the following two routines, and maybe some others */

void rtinit0() {
  /* TODO */
  printf("%sInitializing Node 0...\e[0m\n", node_color(me_0));
  int known_by_0[] = {0,1,3,7};
  initINF(dt0.costs, 0, known_by_0);

  advertise(me_0, known_by_0);
}

void rtupdate0(struct rtpkt *rcvdpkt) {
  //response_doer(rcvdpkt, me_0, dt0.costs[me_0]);
}

void printdt0(struct distance_table *dtptr) {
  printf("                via     \n");
  printf("   D0 |    1     2    3 \n");
  printf("  ----|-----------------\n");
  printf("     1|  %3d   %3d   %3d\n",dtptr->costs[1][1],
	 dtptr->costs[1][2],dtptr->costs[1][3]);
  printf("dest 2|  %3d   %3d   %3d\n",dtptr->costs[2][1],
	 dtptr->costs[2][2],dtptr->costs[2][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][1],
	 dtptr->costs[3][2],dtptr->costs[3][3]);
}

void linkhandler0(int linkid, int newcost) {
  /* DON'T CHANGE */
}

