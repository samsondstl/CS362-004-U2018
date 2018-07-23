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

   printf("UNIT TEST 4: Not Enough Coins\n");
   state.numBuys                 = 1;
   state.coins                   = 5;
   state.supplyCount[adventurer] = 1;
   ret = buyCard(adventurer, g);

   assertTrue(ret                           == -1);
   assertTrue(state.handCount[player1]      == prevState.handCount[player1]);
   assertTrue(state.deckCount[player1]      == prevState.deckCount[player1]);
   assertTrue(state.discardCount[player1]   == prevState.discardCount[player1]);
   assertTrue(state.coins                   == 5);
   assertTrue(state.numBuys                 == 1);
   assertTrue(state.supplyCount[adventurer] == 1);

   state = prevState; 

   printf("UNIT TEST 4: Successfully Buy Card\n");
   state.numBuys                 = 1;
   state.coins                   = 6;
   state.supplyCount[adventurer] = 1;
   ret = buyCard(adventurer, g);

   assertTrue(ret                           == 0);
   assertTrue(state.handCount[player1]      == prevState.handCount[player1]);
   assertTrue(state.deckCount[player1]      == prevState.deckCount[player1]);
   assertTrue(state.discardCount[player1]   == prevState.discardCount[player1] + 1);  
   assertTrue(state.coins                   == 0);
   assertTrue(state.numBuys                 == 0);
   assertTrue(state.supplyCount[adventurer] == 0);

   state = prevState;

   printf("UNIT TEST 4: No Buys Left\n");
   state.numBuys                 = 0;
   state.coins                   = 6;
   state.supplyCount[adventurer] = 1;
   ret = buyCard(adventurer, g);

   assertTrue(ret                           == -1);
   assertTrue(state.handCount[player1]      == prevState.handCount[player1]);
   assertTrue(state.deckCount[player1]      == prevState.deckCount[player1]);
   assertTrue(state.discardCount[player1]   == prevState.discardCount[player1]);
   assertTrue(state.coins                   == 6);
   assertTrue(state.numBuys                 == 0);
   assertTrue(state.supplyCount[adventurer] == 1);  

   printf("UNIT TEST 4: No Cards Left\n"); 
   state.numBuys                 = 1;
   state.coins                   = 6;
   state.supplyCount[adventurer] = 0;

   assertTrue(ret                           == -1);
   assertTrue(state.handCount[player1]      == prevState.handCount[player1]);
   assertTrue(state.deckCount[player1]      == prevState.deckCount[player1]);
   assertTrue(state.discardCount[player1]   == prevState.discardCount[player1]);
   assertTrue(state.coins                   == 6);
   assertTrue(state.numBuys                 == 1);
   assertTrue(state.supplyCount[adventurer] == 0);

   return 0;
}
