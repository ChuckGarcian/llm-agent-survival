#include "stdio.h"
#include "random.h"
#include "agent_manager.h"
#include "graphics.h"

void agtClientUpdate(struct agent *agent) 
{  
  moveAgent (agent, S);
}

int main (void)
{
  struct masf_options opts;
  agent_init (0);
  start_sim ();
}
