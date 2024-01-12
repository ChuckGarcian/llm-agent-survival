#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "raylib.h"
#include "const.h"
#include "agent_manager.h"

extern void agtClientUpdate (struct agent *agt);

static void initAgents(struct agent *agents, size_t cnt);
static void updateSystemState(struct agent *agents, size_t cnt);
static void drawAgents(struct agent *agents, size_t cnt);
static void drawGrid (void);
static int randGet(int min, int max);

  
int main( void)
{
  int cnt = 1;
  struct agent agents[cnt];
  initAgents(agents, cnt);
  initManager (agents, cnt, WORLD_SIZE);
  Camera camera = {0};
  
  InitWindow(SCRNW, SRCHT, "Agent Simulation");
  SetTargetFPS(1);
  
  while (!WindowShouldClose())
  {
    // Update
    updateSystemState(agents, cnt);

    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);
    drawGrid ();
    drawAgents(agents, cnt);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}


/*
 * Populates emtpy array 'AGENTS' with randomly initilized agent objects 
 */    
static void initAgents (struct agent *agents, size_t cnt)
{
  while (cnt--)
  {
    struct agent *agt = &agents[cnt];
    agt->posX = CENTER_X;
    agt->posY = CENTER_Y;
    // agt->posX = randGet(0, SCRNW);
    // agt->posY = randGet(0, SRCHT);
    assert(agt->posX < SCRNW);
    assert(agt->posY < SRCHT);

    agt->perceptual_radius = 2;
    agt->action_radius = 2;

    agt->updateAgent = &agtClientUpdate;
  }
}

static int randGet(int min, int max)
{
  return (rand() % (abs(max - min) + 1) + min);
}

/* 
 * Update the state of the entire system by a timestep
 */
static void updateSystemState(struct agent *agents, size_t cnt)
{
  while (cnt--)
  {
    struct agent *agt = &agents[cnt];
    agt->updateAgent (agt);
  }
}


/*
 * Draw agents array 'AGENTS' of count 'CNT' to winow
 */
static void drawAgents(struct agent *agents, size_t cnt)
{
  while (cnt--)
  {
    struct agent *agt = &agents[cnt];
    int size = FACTOR; 
    DrawRectangle(agt->posX * FACTOR, agt->posY * FACTOR, size, size, BLACK);
  }
}


/*
 * Draw A grid  
*/
static void drawGrid (void)
{

  for (int col = 0; col < WORLD_SIZE; col++)
  {
    for (int row = 0; row < WORLD_SIZE; row++)
    {
     DrawRectangleLines (col * FACTOR, row * FACTOR, FACTOR, FACTOR, BLACK);
    }
  }
}