#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>

void assertTrue(int isTrue)
{
   if (isTrue)
   {
      printf("Passed\n");
   }
   else
   {
      printf("FAILED\n");
   }
}

int main()
{
   int k[10] = {smithy, adventurer, village, steward, embargo, mine, great_hall, feast, minion, baron};

   int ret;

   struct gameState prevState;
   struct gameState state;
   struct gameState *g = &state;

   ret = initializeGame(2, k, 33, g);
   assertTrue(ret == 0);

   prevState = state;

   printf("UNIT TEST 1: Game Not Over\n");
   ret = isGameOver(g);

   assertTrue(ret == 0); 

   printf("UNIT TEST 1: Game Over (Provinces Gone)\n");
   state.supplyCount[province] = 0;
   ret = isGameOver(g);

   assertTrue(ret == 1);   

   state = prevState;

   printf("UNIT TEST 1: Game Not Over (1 Supply Empty)\n");
   state.supplyCount[village] = 0;
   ret = isGameOver(g);

   assertTrue(ret == 0);

   printf("UNIT TEST 1: Game Not Over (2 Supplies Empty)\n");
   state.supplyCount[steward] = 0;
   ret = isGameOver(g);

   assertTrue(ret == 0);

   printf("UNIT TEST 1: Game Over (3 Supplies Empty)\n");
   state.supplyCount[baron] = 0;
   ret = isGameOver(g);

   assertTrue(ret == 1);

   return 0;
}
