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
  int cnt = 3;
  assert (cnt < WD_COLS * WD_ROWS);

  struct agent agents[cnt];
  initAgents(agents, cnt);
  am_initManager (agents, cnt, WD_ROWS, WD_COLS);
  
  InitWindow(SCRNW, SRCHT, "Agent Simulation");
  SetTargetFPS(3);
  
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
  am_destroyManager();
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
    agt->posX = randGet(0, WD_COLS);
    agt->posY = randGet(0, WD_ROWS);


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
    int size = CELL_SIZE; 
    DrawRectangle(agt->posX * CELL_SIZE, agt->posY * CELL_SIZE, size, size, BLACK);
  }
}

/*
 * Draw A grid  
*/
static void drawGrid (void)
{

  for (int col = 0; col < WD_COLS; col++)
  {
    for (int row = 0; row < WD_ROWS; row++)
    {
     DrawRectangleLines (col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE, BLACK);
    }
  }
}