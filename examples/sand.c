#include "stdio.h"

#include "random.h"
#include "agent_manager.h"
#include "graphics.h"

void agtClientUpdate(struct agent *agent) 
{  
  moveAgent (agent, S);
}

int main (int)
{
  start_sim ();
}