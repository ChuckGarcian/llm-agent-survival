#include <stdbool.h>
#include <assert.h>

#include "util/list.h"
#include "agent.h"

/* Enum Helpers */
enum dir {N, S, W, E};

/* Manager Life Cycle */
void am_initManager (struct agent *, size_t, size_t, size_t);
void am_destroyManager (void); 

/* Agent World Perception Information */
void am_getSuroundingEnt(const struct agent, struct list *);
enum dir am_getDirectionFromAToB (const struct agent, const struct agent_base);
bool am_validPos (int posX, int posY);

/* Agent Movement */
bool am_moveAgent (struct agent *, enum dir);