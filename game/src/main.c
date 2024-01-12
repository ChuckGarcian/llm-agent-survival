#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "raylib.h"
#include "agent.h"

#define SCRNW 1000
#define SRCHT 1000
#define CENTER_X SCRNW / 2
#define CENTER_Y SRCHT / 2

static void initAgents (struct agent *agents, size_t cnt);
static void updateSystemState (void);
static void drawAgents (struct agent *agents, size_t cnt);
static int randGet (int min, int max);

void test(int a)
{
  printf("Helllo World! in=%d \n", a);
}

int main(void)
{
  printf("Calling Now \n");
  struct agent agt = {.funcptr = &test};
  agt.funcptr(3);
  return;
    const int screenWidth = SCRNW;
    const int screenHeight = SRCHT;
    int cnt = 5; 
    
    struct agent agents[cnt];
    initAgents(agents, cnt);

    InitWindow(screenWidth, screenHeight, "Agent Simulation");
    SetTargetFPS(60);

    while (!WindowShouldClose())    
    {
      // Update
      updateSystemState();
      
      // Draw
      BeginDrawing();
        ClearBackground(RAYWHITE);
        drawAgents (agents, cnt);
      EndDrawing();
    }

    CloseWindow();
    return 0;
}

/* Populates emtpy array 'AGENTS' with randomly initilized agent objects */
static void initAgents (struct agent *agents, size_t cnt)
{
  while (cnt--)
  {
    struct agent *agt = &agents[cnt];
    agt->posX = randGet (0, SCRNW);
    agt->posY = randGet(0, SRCHT); 
    assert (agt->posX < SCRNW);
    assert (agt->posY < SRCHT);

    agt->perceptual_radius = 2;
    agt->action_radius = 2;
  }
}

static int randGet(int min, int max)
{
  return (rand()%(abs(max - min) + 1) + min);   
}

/* Updates the state of the entire system by a timestep. */
static void updateSystemState(void)
{
 
}
  /*
    Iterate through agents and update their indivual state.
    i.e for each agent, we input current state information such perceptual
    and it outputs the list of actions such as eat, kill, move
  */


static void drawAgents(struct agent *agents, size_t cnt)
{
  while (cnt--)
  {
    struct agent *agt = &agents[cnt];
    
    int size = 50;
    DrawRectangle (agt->posX - size, agt->posY - size, size, size, BLACK);
  }
}
