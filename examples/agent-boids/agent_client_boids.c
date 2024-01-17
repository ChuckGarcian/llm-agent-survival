#include "../src/util/random.h"
#include "../src/agent_manager.h"
#include "stdio.h"
#include "config.h"
#include "../src/graphics.h"

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
  list_shuffle (&surAgts);
  // While there are still entities in the surroundingEntities list
  while (!list_empty(&surAgts))
  {
    struct list_elem *entityElement = list_pop_front(&surAgts);
    struct agent_base *entity = getAgentFromElement(entityElement);
    /////
    bool wasMoveSuccessful;
    enum dir directionToEntity = getDirectionFromAgentToAgent(*agent, *entity);
    if (getDistanceFromAgentToAgent(*agent, *entity) < 6)
      wasMoveSuccessful = moveAgent(agent, getOpposite (directionToEntity));

    ////
    if (entity->ID > agent->my_base.ID)
      continue;
    directionToEntity = getDirectionFromAgentToAgent(*agent, *entity);
    arr[directionToEntity]++;
    numAgents++;
  }

  if (numAgents != 0)
  {
    int max = -1;
    int j = 0;
    for (int i = 0; i < 4; i++)
    {
      if (arr[i] > max)
      {
        max = arr[i];
        j = i;
      }
    }

    printf("avgDir=%d\n", j);
    agent->my_base.heading = j;
  }
  else
  {
    agent->my_base.heading = getRandomDirection();
  }
  if (agent->my_base.ID < 10)
    moveMany(agent, agent->my_base.heading, 5);
  else
    moveAgent(agent, agent->my_base.heading);

  //  Get the direction from the agent to the entity
  //  And try to move the agent in the direction of the entity
}

int main (void)
{
  start_sim ();
}

//   // list_shuffle (&surAgts);
//   randMove (agent);
// }