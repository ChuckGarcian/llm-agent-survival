#include "agent_manager.h"

void agtClientUpdate (struct agent *agt) 
{
  assert (moveAgent(agt, N));
  printf("movin up %d\n", agt->posY);
  
}