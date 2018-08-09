#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int numErrors = 0;

void assertTrue(int isTrue)
{
   if (!isTrue)
   {
      numErrors++;
      printf("FAILED\n");
   }
}

int main()
{
   srand(time(NULL));

   int k[10] = {smithy, adventurer, village, steward, embargo, mine, great_hall, feast, minion, baron};

   int numRuns    = 100;
   int numPlayers = 4;

   int ret;

   struct gameState prevState;
   struct gameState state;
   struct gameState *g = &state;

   int run;
   for (run = 0; run < numRuns; run++)
   {
      ret = initializeGame(numPlayers, k, rand() % 10000, g);
      assertTrue(ret == 0);

      int currPlayer = rand() % numPlayers;
      state.whoseTurn = currPlayer;

      state.supplyCount[smithy]++;
      gainCard(smithy, g, 2, currPlayer);

      prevState = state;

      printf("SMITHY: Run = %d Player = %d\n", run + 1, currPlayer + 1);
      cardEffect(smithy, rand() % 10, rand() % 10, rand() % 10, g, state.handCount[currPlayer] - 1, 0);

      int player;
      for (player = 0; player < numPlayers; player++)
      {
         if (player == currPlayer)
         {
            assertTrue(state.handCount[player]    == prevState.handCount[player] + 2);
         }
         else
         {
            assertTrue(state.handCount[player]    == prevState.handCount[player]);
            assertTrue(state.deckCount[player]    == prevState.deckCount[player]);
            assertTrue(state.discardCount[player] == prevState.discardCount[player]);  
         }
      }
   }

   printf("Errors: %d\n", numErrors);

   return 0;
}
