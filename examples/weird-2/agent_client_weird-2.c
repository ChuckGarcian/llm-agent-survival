#include "../src/util/random.h"
#include "../src/agent_manager.h"
#include "../src/graphics.h"
#include "stdio.h"
#include "config.h"

// bool bufferedMove (struct agent , enum dir d)
// {
//   bool wasMoveSuccessful;
  
//   if (getDistanceFromAgentToAgent (*agent, *entity) < 10)
//     wasMoveSuccessful = moveAgent(agent, getOpposite (directionToEntity)); 
//   else 
//     wasMoveSuccessful = moveAgent (agent, directionToEntity);
//   return wasMoveSuccessful;
// }

void agtClientUpdate(struct agent *agent)
{
  // Create a list to hold the entities surrounding the agent
  struct list surAgts;
  // printAgent(*agent);

  // Populate the list with the entities surrounding the agent
  getSurroundingAgents(*agent, &surAgts);

  // If there are no entities surrounding the agent, move the agent in a random direction
  int numAgents = 0;
  int arr[4] = {0, 0, 0, 0}; 
  // While there are still entities in the surroundingEntities list
  while (!list_empty(&surAgts))
  {
    struct list_elem *entityElement = list_pop_front(&surAgts);
    struct agent_base *entity = getAgentFromElement(entityElement);
    enum dir directionToEntity = getDirectionFromAgentToAgent(*agent, *entity);
    arr[directionToEntity]++;
    numAgents++;
  }
  
  if (numAgents != 0)
  {
    int max = -1;
    int j = 0;
    for (int i = 0 ; i < 4; i ++)
    {
      if (arr[i] > max)
      {
        max = arr[i];
        j = i;
      }
    }
    printf ("avgDir=%d\n", j);
    agent->my_base.heading = j;
  } else {
    agent->my_base.heading = getRandomDirection ();
  }
  moveAgent (agent, agent->my_base.heading);

    //  Get the direction from the agent to the entity
  //  And try to move the agent in the direction of the entity
  
  
}

int main (int)
{
  start_sim();
}
  