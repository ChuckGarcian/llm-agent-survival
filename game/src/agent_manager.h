enum dir {N, S, W, E};
enum entities {FOOD, AGENT};

void initManager (struct agent *, size_t);

/* Agent World Perception Information */
struct list getSuroundingEnt(const struct agent);
enum dir getDirectionFromAToB (const struct agent, const struct agent);

/* Agent Movement */
int move (struct agent *);


