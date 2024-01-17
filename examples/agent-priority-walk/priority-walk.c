/*
  Gives priority to agents closests to this agent, when selecting
  a direction to move in.
*/

#include "../src/util/random.h"
#include "../src/agent_manager.h"
#include "../src/graphics.h"
#include "stdio.h"
#include "config.h"

int numberPaces = 10;

void agtClientUpdate (struct agent *agent)
{
  // Create a list to hold the entities surrounding the agent
  struct list surAgts;

  // Populate the list with the entities surrounding the agent
  getSurroundingAgents(*agent, &surAgts);

  // If there are no entities surrounding the agent, move the agent in a random direction

  // While there are still entities in the surroundingEntities list
  while (!list_empty(&surAgts))
  {
    struct agent_base *entity = getClosestAgent (agent, &surAgts);
    
    //  getAgentFromElement(entityElement);

    //  Get the direction from the agent to the entity
    //  And try to move the agent in the direction of the entity
    if (entity->ID < agent->my_base.ID)
    {
      // Try to move towards the agent numberPaces times
      int numberMoves = numberPaces;
      int oldMvs = 0;
      do
      {
        enum dir directionToEntity = getDirectionFromAgentToAgent(*agent, *entity);
        numberMoves = moveMany (agent, directionToEntity, numberMoves);     
        if (oldMvs == numberMoves) return;
        oldMvs = numberMoves;
      } while (numberMoves > 0);
    }
    
  }

  int numberMoves = numberPaces;
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