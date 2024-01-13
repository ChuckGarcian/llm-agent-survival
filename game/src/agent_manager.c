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

struct agent_base **world;

static void populateWorld (struct agent *agents, size_t cnt);

/*
 *  Initialize and create new world 
 */
void am_initManager (struct agent *agents, size_t cnt, size_t wdR_, size_t wdC_)
{
  // Allocate and initialize 2d world array
  assert (agents);
  wdR = wdR_;
  wdC = wdC_;
  world = (struct agent_base **) calloc (sizeof(struct agent_base *), wdR);
  assert (world);

  while (wdR_--)
  {
    world[wdR_] = (struct agent_base *) calloc (sizeof(struct agent_base), wdC_);
    assert (world[wdR_]);
  }

  populateWorld (agents, cnt); 
}

/* 
 * Free World Resources
 */
void am_destroyManager (void)
{
  for (int row = 0; row < wdR; row++)
    free (world[row]);
}

/*
 * Populate list 'RES' with the entities within the perceptual radius of agent
 * 'AGT'
 */
void am_getSuroundingEnt(const struct agent agt, struct list *res)
{
  list_init (res);
  int rad = agt.perceptual_radius;
  int strtX = agt.posX - rad;
  int strtY = agt.posY - rad;
  int endX = agt.posX + rad;
  int endY = agt.posY + rad;
  printf("agt.posX: %d, agt.posY: %d\n", agt.posX, agt.posY);
  printf("rad: %d\n", rad);
  printf("strtX: %d\n", strtX);
  printf("strtY: %d\n", strtY);
  printf("endX: %d\n", endX);
  printf("endY: %d\n", endY);
  for (int row = strtY; row <= endY; row++)
  {
    for (int col = strtX; col <= endX; col++)
    {
      //printf("row: %d, col: %d\n", row, col);

      // Only valid cordinates
      if (!inBnd(col, wdC) || !inBnd(row, wdR) || world[row][col].ID == NONE) continue;
      if (col == agt.posX && row == agt.posY) continue;
      printf(" Added \n");
      list_push_front (res, &world[row][col].elem);
    }
  }
  printf ("Done In GetSurround \n \n");
}

// TODO: Rewrite better
/*
 *  Return the cardinal direction to make agent A closer to B
 */
enum dir am_getDirectionFromAToB (const struct agent A, const struct agent_base B)
{
  int dx = abs(A.posX - B.posX);
  int dy = abs(A.posY - B.posY);
  printf("dx: %d, dy: %d\n", dx, dy);
  printf("A.posX: %d, A.posY: %d\n", A.posX, A.posY);
  printf("B.posX: %d, B.posY: %d\n", B.posX, B.posY);
  if (dx == 0 && dy == 0) assert (0);
  
  if (dx > dy)    
    if (A.posX - B.posX < 0)
      return E;
      // East
    else
    {
      return W;
      // West
    }
  // Return the enum dir to make dx small
  else
   if (A.posY - B.posY < 0)
   {
     return S;
     // South
   }
   else
   {
     return N;
     // North
   }
  
  assert (0);
   // Return the enum dir to make dy small
}

/* 
 * Check if the cordinate pair 'POSX' and 'POSY' are valid world position
 */
bool am_validPos (int posX, int posY) 
{ 
  bool xB = inBnd(posX, wdC);
  bool yB = inBnd(posY, wdR); 
  return  xB && yB && (world[posY][posX].ID == NONE);
}

/* Agent Movement */
bool am_moveAgent (struct agent *agt, enum dir d)
{
 int dx = dirDelta[d][0];
 int dy = dirDelta[d][1];
 int newX = agt->posX + dx;
 int newY = agt->posY + dy;

 if (!am_validPos (newX, newY))
   return false;  
   
 world[agt->posY][agt->posX].ID = NONE;
 world[newY][newX].ID = AGENT;
 world[newY][newX].posX = newX;
 world[newY][newX].posY = newY;
 agt->posX = newX;
 agt->posY = newY;
 
 return true;
}

static int randGet(int min, int max)
{
  return (rand() % (abs(max - min) + 1) + min);
}

static void populateWorld(struct agent *agents, size_t cnt)
{
  while (cnt--)
  {
    struct agent *agt = &agents[cnt];
    while (!am_validPos(agt->posX, agt->posY))
    {
      agt->posX = randGet(0, wdC);
      agt->posY = randGet(0, wdR);
    }
    int posX = agents[cnt].posX;
    int posY = agents[cnt].posY;
    
    assert (am_validPos(posX, posY));
    world[posY][posX].ID = agt->ID;
    world[posY][posX].posX = posX;
    world[posY][posX].posY = posY;
  }
}
