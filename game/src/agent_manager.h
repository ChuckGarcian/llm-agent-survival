#include <stdbool.h>
#include <assert.h>

enum dir {N, S, W, E};
enum entities {NONE, FOOD, AGENT};

/* Manager Life Cycle */
void initManager (struct agent *, size_t, size_t);
void destroyManager (void); 

/* Agent World Perception Information */
struct list getSuroundingEnt(const struct agent);
enum dir getDirectionFromAToB (const struct agent, const struct agent);
bool validPos (int posX, int posY);

/* Agent Movement */
int move (struct agent *);



