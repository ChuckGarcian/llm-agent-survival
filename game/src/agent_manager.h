enum dir {N, S, W, E};
enum entities {FOOD, AGENT, NONE};

/* Manager Life Cycle */
void initManager (struct agent *, size_t, size_t);
void destroyManager (void); 

/* Agent World Perception Information */
struct list getSuroundingEnt(const struct agent);
enum dir getDirectionFromAToB (const struct agent, const struct agent);

/* Agent Movement */
int move (struct agent *);


