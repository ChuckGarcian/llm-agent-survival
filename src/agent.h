enum entities {NONE, FOOD, AGENT,};

/* TODO: This should be moved to agent_manager.h, as it pertains to general
   Agent data rather then client agent data */

/* Base agent data used in agent manager */
struct agent_base 
{
  struct list_elem elem; /* Used to return a list of agents in agent client */
  int ID;                /* Categorical ID - i.e NONE, FOOD, AGENT */
  int posX;
  int posY; 
};

/* Agent data used in the agent client */
struct agent
{
  struct agent_base my_base;
  int perceptual_radius;
  int action_radius;
  void (*updateAgent)(struct agent *);
  /* C function pointers cheatsheet */
};

//evoid updateAgent (static agent);
