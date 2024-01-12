/*
 *  Facilitates all agent behavior on behalf of each agent client
 * TODO: Rename this file to world manager; it managers generally entities - not
 *       just agents
 */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "agent_manager.h"

#define inBnd(pos, wdA) ((pos) >= 0 && (pos) < (wdA))

int dirDelta[4][2] = {{0,-1}, {0,1}, {-1,0}, {1,0}};
int wdR;
int wdC;
enum entities **world;

static void populateWorld (struct agent *agents, size_t cnt);

/*
 *  Initialize and create new world 
 */
void initManager (struct agent *agents, size_t cnt, size_t wdR_, size_t wdC_)
{
  // Allocate and initialize 2d world array
  assert (agents);
  wdR = wdR_;
  wdC = wdC_;
  world = (enum entities **) calloc (sizeof(enum entities *), wdR);
  assert (world);

  while (wdR_--)
  {
    printf ("wdR = %d \n", wdR_);
    world[wdR_] = (enum entities *) calloc (sizeof(enum entities), wdC_);
    assert (world[wdR_]);

  }

  populateWorld (agents, cnt); 
}


/* 
 * Free World Resources
 */
void destroyManager (void)
{
  for (int row = 0; row < wdR; row++)
    free (world[row]);
}


struct list getSuroundingEnt(const struct agent agt);


enum dir getDirectionFromAToB (const struct agent A, const struct agent B);
  

/* 
 * Check if the cordinate pair 'POSX' and 'POSY' are valid world position
 */
bool validPos (int posX, int posY)
{ 
  return world[posY][posX] == NONE && inBnd(posX, wdC) && inBnd(posY, wdR);  
}


/* Agent Movement */
bool moveAgent (struct agent *agt, enum dir d)
{
 int dx = dirDelta[d][0];
 int dy = dirDelta[d][1];
 int newX = agt->posX + dx;
 int newY = agt->posY + dy;
 
 assert (validPos (newX, newY));
 if (!validPos (newX, newY))
   return false;  
 
 agt->posX = newX;
 agt->posY = newY;
 return true;
}

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
