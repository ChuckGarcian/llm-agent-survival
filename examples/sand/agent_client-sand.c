#include "stdio.h"

#include "../src/util/random.h"
#include "../src/agent_manager.h"
#include "../src/graphics.h"

void agtClientUpdate(struct agent *agent) 
{  
  moveAgent (agent, S);
}

int main (int)
{
  start_sim ();
}