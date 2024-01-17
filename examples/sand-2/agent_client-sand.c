#include "../src/util/random.h"
#include "../src/agent_manager.h"
#include "stdio.h"

void agtClientUpdate(struct agent *agent) 
{  
 
  if(!moveAgent (agent, S)) moveAgent (agent, N);
 
}