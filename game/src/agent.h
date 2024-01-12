/* Agent Object */
struct agent
{
  int posX;
  int posY;

  int perceptual_radius;
  int action_radius;
  void (*funcptr)(int);
  /* C function pointers cheatsheet */
};

//evoid updateAgent (static agent);
