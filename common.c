#include "common.h"
void initINF(int dt[TABLE_ENTRIES][TABLE_ENTRIES], int pos, int known[TABLE_ENTRIES])
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            dt[i][j] = INFINITY;

    for (int i = 0; i < 4; i++)
        dt[pos][i] = known[i];
}