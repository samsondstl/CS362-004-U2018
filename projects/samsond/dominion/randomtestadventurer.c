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
   
   ret = initializeGame(numPlayers, k, 33, g);
   assertTrue(ret == 0);
   
   int run;
   for (run = 0; run < numRuns; run++)
   {
      int currPlayer = rand() % numPlayers;
      state.whoseTurn = currPlayer;     
 
      state.supplyCount[adventurer]++; 
      gainCard(adventurer, g, 2, currPlayer);

      prevState = state;
       
      printf("ADVENTURER: Run = %d Player = %d\n", run + 1, currPlayer + 1);
      cardEffect(adventurer, rand() % 10, rand() % 10, rand() % 10, g, state.handCount[currPlayer] - 1, 0);
     
      int player;
      for (player = 0; player < numPlayers; player++)
      {
         if (player == currPlayer)
         {
            int card;

            int prevTreasure = 0;
            for (card = 0; card < prevState.handCount[player]; card++)
            {
               if (    prevState.hand[player][card] == copper 
                    || prevState.hand[player][card] == silver 
                    || prevState.hand[player][card] == gold)
               {
                  prevTreasure++;
               }
            }

            int newTreasure = 0;
            for (card = 0; card < state.handCount[player]; card++)
            {
               if (    state.hand[player][card] == copper
                    || state.hand[player][card] == silver
                    || state.hand[player][card] == gold)
               {
                  newTreasure++;
               }
            }

            int treasureAvailableToDraw = 0;
            for (card = 0; card < prevState.deckCount[player]; card++)
            {
               if (    prevState.deck[player][card] == copper
                    || prevState.deck[player][card] == silver
                    || prevState.deck[player][card] == gold)
               {
                  treasureAvailableToDraw++;
               }
            }
            for (card = 0; card < prevState.discardCount[player]; card++)
            {
               if (    prevState.discard[player][card] == copper
                    || prevState.discard[player][card] == silver
                    || prevState.discard[player][card] == gold)
               {
                  treasureAvailableToDraw++;
               }
            }

            if (treasureAvailableToDraw >= 2)
            {
               assertTrue(newTreasure - prevTreasure == 2);
            }
            else
            {
               assertTrue(newTreasure - prevTreasure == treasureAvailableToDraw);
            }
            assertTrue(state.handCount[player] == prevState.handCount[player] + (newTreasure - prevTreasure) - 1);
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
