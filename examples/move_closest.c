/*
  In this example agent selects a direction to move once - There are two different
  ways an agent will move:
    1. An agent will selects closest high priority agent to itself and move 
    in that direction.
    2. If there are no high priority agents in it's vicinity, it will move in
    a random direction.
*/

#include "random.h"
#include "agent_manager.h"
#include "graphics.h"
#include "stdio.h"

int num_paces = 10;

void agtClientUpdate (struct agent *agent)
{
  struct list surAgts;
  getSurroundingAgents(*agent, &surAgts);
  list_shuffle (&surAgts);

  // Try to move in the direction of closest agent
  while (!list_empty(&surAgts))
  {
    struct agent_base *tgt = getClosestAgent (agent, &surAgts);
    enum dir vector = getDirectionFromAgentToAgent(*agent, *tgt);

    if (tgt->ID < agent->my_base.ID)
    {
      int num_moves = num_paces;
      int old_moves = 0;
      
      // Continue moving the agent toward target agent, as long as there are moves left
      do {
       
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
  struct masf_options opts;
  opts = agent_init (0);
  opts.fps = 10;
  agent_setattr (opts);
  start_sim();
}