/*
  In this example, I tried to 
  agents with lower id have greater priority to move autonomously, were as lesser
  priority agents are forced to move towards higher priority agents.
*/

#include "../src/util/random.h"
#include "../src/agent_manager.h"
#include "../src/graphics.h"
#include "stdio.h"
#include "config.h"

int num_paces = 10;

void agtClientUpdate (struct agent *agent)
{
  struct list surAgts;
  getSurroundingAgents(*agent, &surAgts);

  // Try to move in the direction of closest agent
  while (!list_empty(&surAgts))
  {
    struct agent_base *tgt = getClosestAgent (agent, &surAgts);
  
    if (tgt->ID < agent->my_base.ID)
    {
      int num_moves = num_paces;
      int old_moves = 0;
      
      // Continue moving the agent toward target agent, as long as there are moves left
      {
        enum dir vector = getDirectionFromAgentToAgent(*agent, *tgt);
        num_moves = moveMany (agent, vector, num_moves);     
        if (old_moves == num_moves) return;
        old_moves = num_moves;
      } while (num_moves > 0);
    }
    
  }

  // There are no lesser priority agents in the immediate vicinity,
  // so move in a random direction
  int numberMoves = num_paces;
  int oldMvs = 0;
  do
  {
    enum dir directionToEntity = getRandomDirection ();
    numberMoves = moveMany (agent, directionToEntity, numberMoves);     
    if (oldMvs == numberMoves) return;
    oldMvs = numberMoves;
  } while (numberMoves > 0);
  
}

int main (int)
{
  start_sim();
}