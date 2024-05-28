#include "random.h"
#include "agent_manager.h"
#include "stdio.h"
#include "graphics.h"

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

    bool wasMoveSuccessful;
    enum dir directionToEntity = getDirectionFromAgentToAgent(*agent, *entity);
    if (getDistanceFromAgentToAgent(*agent, *entity) < 6)
      wasMoveSuccessful = moveAgent(agent, getOpposite (directionToEntity));

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
  struct masf_options opts;
  agent_init (0);
  start_sim ();
}
