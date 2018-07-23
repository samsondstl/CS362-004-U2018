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
   struct gameState prevState;
   struct gameState state;
   struct gameState *g = &state;

   ret = initializeGame(2, k, 33, g);
   assertTrue(ret == 0);

   prevState = state;

   printf("UNIT TEST 3: Add Card To Deck\n");
   ret = gainCard(mine, g, 1, player1);

   assertTrue(ret                         == 0);
   assertTrue(state.handCount[player1]    == prevState.handCount[player1]);
   assertTrue(state.deckCount[player1]    == prevState.deckCount[player1] + 1);
   assertTrue(state.discardCount[player1] == prevState.discardCount[player1]);
   assertTrue(state.supplyCount[mine]     == prevState.supplyCount[mine] - 1);

   state = prevState;

   printf("UNIT TEST 3: Add Card To Hand\n");
   ret = gainCard(great_hall, g, 2, player1);   

   assertTrue(ret                           == 0);
   assertTrue(state.handCount[player1]      == prevState.handCount[player1] + 1);
   assertTrue(state.deckCount[player1]      == prevState.deckCount[player1]);
   assertTrue(state.discardCount[player1]   == prevState.discardCount[player1]);
   assertTrue(state.supplyCount[great_hall] == prevState.supplyCount[great_hall] - 1);  

   state = prevState;

   printf("UNIT TEST 3: Add Card To Discard\n");
   ret = gainCard(feast, g, 3, player1);

   assertTrue(ret                         == 0);
   assertTrue(state.handCount[player1]    == prevState.handCount[player1]);
   assertTrue(state.deckCount[player1]    == prevState.deckCount[player1]);
   assertTrue(state.discardCount[player1] == prevState.discardCount[player1] + 1);
   assertTrue(state.supplyCount[feast]    == prevState.supplyCount[feast] - 1);

   return 0;
}
