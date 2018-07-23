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

   printf("CARD TEST 3: Selected Pile Not In Play\n");
   ret = cardEffect(embargo, 0, 0, 0, g, player1, 0);

   assertTrue(ret == 0);

   assertTrue(state.handCount[player1]    == prevState.handCount[player1] - 1);
   assertTrue(state.deckCount[player1]    == prevState.deckCount[player1]);
   assertTrue(state.discardCount[player1] == prevState.discardCount[player1] + 1);

   assertTrue(state.embargoTokens[0]      == prevState.embargoTokens[0] + 1);
   assertTrue(state.coins                 == prevState.coins + 2);

   assertTrue(state.handCount[player2]    == prevState.handCount[player2]);
   assertTrue(state.deckCount[player2]    == prevState.deckCount[player2]);
   assertTrue(state.discardCount[player2] == prevState.discardCount[player2]);

   state = prevState;

   printf("CARD TEST 3: Embargo Token Added\n");
   state.supplyCount[1] = -1;

   ret = cardEffect(embargo, 1, 0, 0, g, player1, 0);

   assertTrue(ret == -1);

   assertTrue(state.handCount[player1]    == prevState.handCount[player1]);
   assertTrue(state.deckCount[player1]    == prevState.deckCount[player1]);
   assertTrue(state.discardCount[player1] == prevState.discardCount[player1]);

   assertTrue(state.embargoTokens[1]      == prevState.embargoTokens[1]);
   assertTrue(state.coins                 == prevState.coins);

   assertTrue(state.handCount[player2]    == prevState.handCount[player2]);
   assertTrue(state.deckCount[player2]    == prevState.deckCount[player2]);
   assertTrue(state.discardCount[player2] == prevState.discardCount[player2]);

   return 0;
}
