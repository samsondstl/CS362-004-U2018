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

   printf("CARD TEST 2: Draw Two Cards\n");
   ret = cardEffect(steward, 1, 0, 0, g, player1, 0); 

   assertTrue(state.handCount[player1]    == prevState.handCount[player1] + 1);
   assertTrue(state.deckCount[player1]    == prevState.deckCount[player1] - 2);
   assertTrue(state.discardCount[player1] == prevState.discardCount[player1] + 1);

   assertTrue(state.coins                 == prevState.coins);

   assertTrue(state.handCount[player2]    == prevState.handCount[player2]);
   assertTrue(state.deckCount[player2]    == prevState.deckCount[player2]);
   assertTrue(state.discardCount[player2] == prevState.discardCount[player2]);

   state = prevState;

   printf("CARD TEST 2: Gain Two Coins\n");
   ret = cardEffect(steward, 2, 0, 0, g, player1, 0);

   assertTrue(state.handCount[player1]    == prevState.handCount[player1] - 1);
   assertTrue(state.deckCount[player1]    == prevState.deckCount[player1]);
   assertTrue(state.discardCount[player1] == prevState.discardCount[player1] + 1);

   assertTrue(state.coins                 == prevState.coins + 2);

   assertTrue(state.handCount[player2]    == prevState.handCount[player2]);
   assertTrue(state.deckCount[player2]    == prevState.deckCount[player2]);
   assertTrue(state.discardCount[player2] == prevState.discardCount[player2]);

   printf("CARD TEST 2: Trash Two Cards\n");
   state = prevState;

   ret = cardEffect(steward, 3, 0, 1, g, player1, 0);

   assertTrue(state.handCount[player1]    == prevState.handCount[player1] - 3);
   assertTrue(state.deckCount[player1]    == prevState.deckCount[player1]);
// DJS: Updated To Check Two Cards Trashed, Steward Discarded
   assertTrue(state.playedCardCount       == prevState.playedCardCount + 2);
   assertTrue(state.discardCount[player1] == prevState.discardCount[player1] + 1); 

   assertTrue(state.coins                 == prevState.coins);

   assertTrue(state.handCount[player2]    == prevState.handCount[player2]);
   assertTrue(state.deckCount[player2]    == prevState.deckCount[player2]);
   assertTrue(state.discardCount[player2] == prevState.discardCount[player2]);

   return 0;
}
