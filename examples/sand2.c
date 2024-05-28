#include "random.h"
#include "agent_manager.h"
#include "graphics.h"
#include "stdio.h"

void agtClientUpdate(struct agent *agent) 
{  
 
  if(!moveAgent (agent, S)) moveAgent (agent, N);
 
}

int main (int)
{
  start_sim ();
}