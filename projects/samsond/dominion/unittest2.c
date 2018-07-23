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
   int player1 = 0;
   int ret;
   struct gameState state;
   struct gameState *g = &state;

   ret = initializeGame(2, k, 33, g);
   assertTrue(ret == 0);

   int i;
   int coins = 0;
   for (i = 0; i < state.handCount[player1]; i++)
   {
      if (state.hand[player1][i] == copper)
      {
         coins += 1;
      }
      else if (state.hand[player1][i] == silver)
      {
         coins += 2;
      }
      else if (state.hand[player1][i] == gold)
      {
         coins += 3;
      }
   }

   printf("UNIT TEST 2: Determine Coin Count (No Bonus)\n");
   ret = updateCoins(player1, g, 0);

   assertTrue(ret == 0);
   assertTrue(state.coins == coins);

   printf("UNIT TEST 2: Determine Coin Count (w/ Bonus)\n");
   ret = updateCoins(player1, g, 4);
   assertTrue(state.coins == coins + 4);

   return 0;
}
