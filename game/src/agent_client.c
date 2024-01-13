#include "agent_manager.h"

static int randGet(int min, int max)
{
  return (rand() % (abs(max - min) + 1) + min);
}

void agtClientUpdate (struct agent *agt) 
{
  while (!moveAgent(agt, randGet(0,3)));
}