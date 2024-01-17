/*
 *  Facilitates all agent behavior on behalf of each agent client
 * TODO: Rename this file to world manager; it managers generally entities - not
 *       just agents
 */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "agent_manager.h"
#include <math.h>

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
  wdR = wdR_;
  wdC = wdC_;
  assert (agents);

  world = (struct agent_base **) malloc (sizeof(struct agent_base *) * wdR);
  memset (world, NONE, sizeof(struct agent_base *) * wdR);
  assert (world);

  while (wdR_--)
  {
    world[wdR_] = (struct agent_base *) malloc (sizeof(struct agent_base) * wdC_);
    memset (world[wdR_], NONE, sizeof(struct agent_base) * wdC_);
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
void getSurroundingAgents(const struct agent agt, struct list *res)
{
  list_init (res);
  int rad = agt.perceptual_radius;
  int strtX = agt.my_base.posX - rad;
  int strtY = agt.my_base.posY - rad;
  int endX = agt.my_base.posX + rad;
  int endY = agt.my_base.posY + rad;
  
  for (int row = strtY; row <= endY; row++)
  {
    for (int col = strtX; col <= endX; col++)
    {
      // Only valid cordinates
      if (!inBnd(col, wdC) || !inBnd(row, wdR) || world[row][col].ID == NONE) continue;
      if (col == agt.my_base.posX && row == agt.my_base.posY) continue;
      list_push_front (res, &world[row][col].elem);
    }
  }
  
  // Shuffle list to prevent movement biasing
  list_shuffle (res);
}

// TODO: Rewrite better
/*
 *  Return the cardinal direction to make agent A closer to B
 */
enum dir getDirectionFromAgentToAgent (const struct agent A, const struct agent_base B)
{
  int x = A.my_base.posX - B.posX;
  int y = A.my_base.posY - B.posY;
  
  int dx = abs(x);
  int dy = abs(y);
  
  if (dx == 0 && dy == 0) // The two agents are at the same position
    assert(0);  
  
  if (dx > dy) 
    return (x < 0) ? E : W;  // East or West
  else
    return (y < 0) ? S : N;  // South or North

  assert(0);
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

bool agent_list_less(const struct list_elem *a, const struct list_elem *b, void *aux)
{
  struct agent_base *parent = getAgentFromElement ((struct list_elem *) aux);
  struct agent_base *A = getAgentFromElement (a);
  struct agent_base *B = getAgentFromElement (b);
  
  // Calculate the distance between parent and A
  int dxA = parent->posX - A->posX;
  int dyA = parent->posY - A->posY;
  double distA = sqrt(dxA * dxA + dyA * dyA);

  // Calculate the distance between parent and B
  int dxB = parent->posX - B->posX;
  int dyB = parent->posY - B->posY;
  double distB = sqrt(dxB * dxB + dyB * dyB);

  // Compare the distances
  return distA < distB;
}

struct agent_base *getClosestAgent(struct agent *parent, struct list *agtList)
{ 
  list_sort (agtList, agent_list_less, &parent->my_base);
  return getAgentFromElement (list_pop_back (agtList));
}

/* Get the distance from agent A to agent B */
int getDistanceFromAgentToAgent(const struct agent A, const struct agent_base B)
{
  int dxA = A.my_base.posX - B.posX;
  int dyA = A.my_base.posY - B.posY;
  return sqrt(dxA * dxA + dyA * dyA); 
}

/* Agent Movement */
bool moveAgent (struct agent *agt, enum dir d)
{
 int dx = dirDelta[d][0];
 int dy = dirDelta[d][1];
 int newX = agt->my_base.posX + dx;
 int newY = agt->my_base.posY + dy;

 if (!am_validPos (newX, newY))
   return false;  
   
 world[agt->my_base.posY][agt->my_base.posX].ID = NONE;
 world[newY][newX].ID = agt->my_base.ID;
 world[newY][newX].posX = newX;
 world[newY][newX].posY = newY;
 agt->my_base.posX = newX;
 agt->my_base.posY = newY;
 
 return true;
}

/*
* Moves agent 'AGT' in the direction 'D', by 'PACES' number of times.
* Returns the number of sucessfull paces.
*/
int moveMany(struct agent *agt, enum dir d, int paces)
{
  if (paces == 0) return 0;
  while (moveAgent(agt, d) && --paces > 0)
  return paces;
}


/*
* Gaurenteed to move agent 'AGT' in a random direction, unless otherwise locked
*/
void randMove(struct agent *agt)
{
  int desired_move = getRandomDirection();
  int tries = 0;
  while (!moveAgent(agt, desired_move) && tries++ < 5) 
    desired_move = (desired_move + 1) % 4;
}

void printAgent(struct agent agt)
{
    printf("my_base.ID: %d\n", agt.my_base.ID);
    printf("my_base.posX: %d\n", agt.my_base.posX);
    printf("my_base.posY: %d\n", agt.my_base.posY);

    printf("ID: %d\n", agt.my_base.ID);
    printf("posX: %d\n", agt.my_base.posX);
    printf("posY: %d\n", agt.my_base.posY);
    printf("perceptual_radius: %d\n", agt.perceptual_radius);
    printf("action_radius: %d\n", agt.action_radius);
}

int getOpposite (enum dir d)
{
  switch (d)
  {
  case N:
    return S;
  case S:
    return N;
  case E:
    return W;
  case W:
    return E;
  default:
    assert(0);
  }
}

static void populateWorld(struct agent *agents, size_t cnt)
{
  while (cnt--)
  {
    struct agent *agt = &agents[cnt];
    while (!am_validPos(agt->my_base.posX, agt->my_base.posY))
    {
      agt->my_base.posX = random_range(wdC);
      agt->my_base.posY = random_range (wdR);
    }
    int posX = agents[cnt].my_base.posX;
    int posY = agents[cnt].my_base.posY;
    
    assert (am_validPos(posX, posY));
    world[posY][posX].ID = agt->my_base.ID;
    world[posY][posX].posX = posX;
    world[posY][posX].posY = posY;
  }
}
