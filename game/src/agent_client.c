#include "agent_manager.h"
#include "random.h"
// extern int random_range (int n);

void agtClientUpdate (struct agent *agt) 
{
  while (!am_moveAgent(agt, random_range (4)));
  
  struct list sur; // List of enitites surrounding me
  struct list_elem *e;
  
  am_getSuroundingEnt(*agt, &sur);

  for (e = list_begin (&sur); e != list_end (&sur); e = list_next (e))
  {
    struct agent_base *f = list_entry (e, struct agent_base, elem);
    enum dir d = am_getDirectionFromAToB (*agt, *f);
    printf ("Surounding Agent! =%d \n", d);
  }


  
  
}