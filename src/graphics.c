/***
 * At every time step each agent 
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "raylib.h"
#include "agent_manager.h"
#include "util/random.h"
#include "../examples/agent-priority-walk/congif.h"

static void initAgents(struct agent *agents, size_t cnt);
static void updateSystemState(struct agent *agents, size_t cnt);
static void drawAgents(struct agent *agents, size_t cnt);
static void drawGrid (void);

int main( void)
{
  assert (CNT < WD_COLS * WD_ROWS);

  struct agent agents[CNT];
  initAgents(agents, CNT);
  am_initManager (agents, CNT, WD_ROWS, WD_COLS);
  
  InitWindow(SCRNW, SRCHT, "Agent Simulation");
  SetTargetFPS(FPS);
  
  while (!WindowShouldClose())
  {
    // Update
    updateSystemState(agents, CNT);

    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);
    drawGrid ();
    drawAgents(agents, CNT);
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
    agt->my_base.posX = random_range (WD_COLS);
    agt->my_base.posY = random_range (WD_ROWS);
    agt->my_base.ID = cnt + 1;

    agt->perceptual_radius = 6;
    agt->action_radius = 2;
    agt->updateAgent = &agtClientUpdate;
  }
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
    DrawRectangle(agt->my_base.posX * CELL_SIZE, agt->my_base.posY * CELL_SIZE, size, size, BLACK);
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