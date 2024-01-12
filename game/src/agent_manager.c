/*
 *  Facilitates all agent behavior on behalf of each agent client
 * TODO: Rename this file to world manager; it managers generally entities - not
 *       just agents
 */
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "agent.h"
#include "agent_manager.h"
#include "list.h"

static void populateWorld (struct agent *agents, size_t cnt);
static bool validPos (int posX, int posY);
static bool inBnd (int pos);

/* 2d Matrix of sim world */
enum entities **world;
int worldSize;

/*
 *  Initialize and create new world 
 */
void initManager (struct agent *agents, size_t cnt, size_t wrld_sz)
{
  assert (agents);
  worldSize = wrld_sz;
  world = (enum entities **) calloc (sizeof(enum entities *), worldSize);
  assert (world);

  while (wrld_sz--)
  {
    world[wrld_sz] = (enum entities *) calloc (sizeof(enum entities), worldSize);
    assert (world[wrld_sz]);
  }

  populateWorld (agents, cnt); 
}


/* 
 * Free World Resources
 */
void destroyManager (void)
{
  for (int row = 0; row < worldSize; row++)
    free (world[row]);
}


struct list getSuroundingEnt(const struct agent agt);


enum dir getDirectionFromAToB (const struct agent A, const struct agent B);
  

/* Agent Movement */
int move (struct agent * agt);


static void populateWorld(struct agent *agents, size_t cnt)
{
  while (cnt--)
  {
    int posX = agents[cnt].posX;
    int posY = agents[cnt].posY;
    
    assert (validPos(posX, posY));
    
    world[posY][posX] = AGENT;
  }
}


/* 
 * Check if the cordinate pair 'POSX' and 'POSY' are valid world position
 */
static bool validPos (int posX, int posY)
{ 
  return world[posY][posX] != NONE || !inBnd(posX) || !inBnd(posY);  
}


/*
 * Check If the axis point 'POS' is within world boundraries
*/
static bool inBnd (int pos)
{
  return pos >=0 && pos < worldSize;
}