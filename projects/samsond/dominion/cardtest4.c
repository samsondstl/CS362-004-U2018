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
   int player2 = 1;
   int ret;
   struct gameState prevState;
   struct gameState state;
   struct gameState *g = &state;

   ret = initializeGame(2, k, 33, g);
   assertTrue(ret == 0);

   prevState = state;

   printf("CARD TEST 4: Two Treasure Cards Drawn\n");
   cardEffect(adventurer, 0, 0, 0, g, player1, 0);

   assertTrue(state.handCount[player1]    == prevState.handCount[player1]    + 1);
   assertTrue(state.deckCount[player1]    <= prevState.deckCount[player1]    - 2);
   assertTrue(state.discardCount[player1] >= prevState.discardCount[player1] - 1); 

   assertTrue(state.handCount[player2]    == prevState.handCount[player2]);
   assertTrue(state.deckCount[player2]    == prevState.deckCount[player2]);
   assertTrue(state.discardCount[player2] == prevState.discardCount[player2]);

   return 0;
}
