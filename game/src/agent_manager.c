/*
 *  Facilitates all agent behavior on behalf of each agent client
 * TODO: Rename this file to world manager; it managers generally entities - not
 *       just agents
 */
#include <stddef.h>
#include <stdlib.h>
#include "agent.h"
#include "agent_manager.h"
#include "list.h"

static void populateWorld (struct agent *agents, size_t cnt);
static void validPos (struct agent agt);

/* 2d Matrix of sim world */
enum entities *world;

/* Initialize and create new world */
void initManager (struct agent *agents, size_t cnt, size_t wrld_sz)
{
  world = (enum entities *) calloc (size_of(enum entities), wrld_sz);
  assert (world);
}

/* Frees World Resources*/
void destroyManager (void)
{
  free (world);
}


struct list getSuroundingEnt(const struct agent agt);


enum dir getDirectionFromAToB (const struct agent A, const struct agent B);
  

/* Agent Movement */
int move (struct agent * agt);

static void populateWorld(agent *agents, size_t cnt)
{

}
