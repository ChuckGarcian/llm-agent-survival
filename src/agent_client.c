#include "agent_manager.h"
#include "util/random.h"
#include "stdio.h"

// extern int random_range (int n);
void printAgent(struct agent agt) {
    printf("my_base.ID: %d\n", agt.my_base.ID);
    printf("my_base.posX: %d\n", agt.my_base.posX);
    printf("my_base.posY: %d\n", agt.my_base.posY);

    printf("ID: %d\n", agt.my_base.ID);
    printf("posX: %d\n", agt.my_base.posX);
    printf("posY: %d\n", agt.my_base.posY);
    printf("perceptual_radius: %d\n", agt.perceptual_radius);
    printf("action_radius: %d\n", agt.action_radius);
}

void agtClientUpdate (struct agent *agt) 
{  
  // printAgent (*agt);
  while (!am_moveAgent(agt, random_range (4)));

  struct list sur; // List of enitites surrounding me
  am_getSuroundingEnt(*agt, &sur);

  while (!list_empty (&sur))
   {
     struct list_elem *e = list_pop_front (&sur);
     struct agent_base *f = list_entry (e, struct agent_base, elem);
     enum dir d = am_getDirectionFromAToB (*agt, *f);
     bool suc = am_moveAgent (agt, d);
     if (!suc) am_moveAgent(agt, random_range (4));
     printf ("agent_suc  %d \n", suc);
     printf ("direction=%d \n", d); 
   }
  printf ("agent_client \n\n");
  
}