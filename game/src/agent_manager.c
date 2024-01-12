/*
 *  Facilitates all agent behavior on behalf of each agent client
 */
#include <stddef.h>
#include "agent.h"
#include "agent_manager.h"
#include "list.h"


void initManager (struct agent *agents, size_t cnt)
{
  return;
}

/* Agent World Perception Information */
struct list getSuroundingEnt(const struct agent agt) 
{
  struct list a = {0};
  return a;
}


enum dir getDirectionFromAToB (const struct agent A, const struct agent B)
{
  
  return N;
}

/* Agent Movement */
int move (struct agent * agt)
{
  return 0;
}
