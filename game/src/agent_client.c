#include "agent_manager.h"
#include "random.h"
// extern int random_range (int n);

void agtClientUpdate (struct agent *agt) 
{
  while (!moveAgent(agt, random_range (4)));
}