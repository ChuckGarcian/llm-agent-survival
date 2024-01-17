# Agent Framework
Simple framework easily defining multi-agent systems in C. 
## Example - Naive Drone Clusters 
```
void agtClientUpdate(struct agent *agent) 
{
  // Create and populate list with entities surrounding the agent
  struct list surAgts;
  getSurroundingAgents(*agent, &surAgts);

  // We want to make the agent move towards other agents with less ID
  // Ideally, this makes the agents exhibit 'drone' like behavior'
  while (!list_empty(&surAgts))
  {

    struct list_elem *entityElement = list_pop_front(&surAgts);
    struct agent_base *entity = getAgentFromElement(entityElement);

    if (entity->ID < agent->my_base.ID)
    {
      enum dir directionToEntity = getDirectionFromAgentToAgent(*agent, *entity);
      bool wasMoveSuccessful = moveAgent(agent, directionToEntity);
      if (wasMoveSuccessful)
        return;
    }
  }
  
  // No lesser agents surrounding this agent, so just randomly move
  randMove (agent); 
}
```
![output](https://github.com/ChuckGarcian/multi-agent-system-framework/assets/76849825/14a9ac34-c363-4a42-90a9-f43775edc834)


## TODO
 - [ ] Move initAgents to agent_manager so the world 2d array and initAgents are
       are integrated.
