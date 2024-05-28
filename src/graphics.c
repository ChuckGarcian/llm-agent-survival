/***
 * At every time step each agent 
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "raylib.h"
#include "agent_manager.h"
#include "random.h"
#include "graphics.h"

#define ASSERTF_DEF_ONCE
#include "assertf.h"

extern void agtClientUpdate(struct agent *agent);
struct masf_options options; 

static void initAgents(struct agent *agents, size_t cnt);
static void updateSystemState(struct agent *agents, size_t cnt);
static void drawAgents(struct agent *agents, size_t cnt);
static void drawGrid (void);

struct masf_options agent_init (struct masf_options *settings)
{
  if (settings)
  {
    options = *settings;
  }
  else 
  {
    options.wd_rows = 200;
    options.wd_cols = 350;
    options.center_y = options.wd_rows / 2;
    options.center_x = options.wd_cols / 2;
    options.cnt = 500;
    options.cell_size = 5;
    options.screen_width = options.wd_cols * 5;
    options.screen_height = options.wd_rows * 5;
    options.fps = 20;
  }
  options.initialized = 1;
  return options;
}

int agent_setattr (struct masf_options new_options)
{
  options.wd_rows = new_options.wd_rows;
  options.wd_cols = new_options.wd_cols;
  options.center_y = new_options.center_y;
  options.center_x = new_options.center_x;
  options.cnt = new_options.cnt;
  options.cell_size = new_options.cell_size;
  options.screen_width = new_options.screen_width;
  options.screen_height = new_options.screen_height;
  options.fps = new_options.fps;  
}

void start_sim (void)
{
  assertf(options.initialized == 1, "Not Initialized when supposed to be");
  assertf(options.cnt < options.wd_cols * options.wd_rows, "Invalid Set Options");

  struct agent agents[options.cnt];
  initAgents(agents, options.cnt);
  am_initManager (agents, options.cnt, options.wd_rows, options.wd_cols);
  
  InitWindow(options.screen_width, options.screen_height, "Agent Simulation");
  SetTargetFPS(options.fps);
  
  // char *c = NULL;
  // int size;
  // getline (&c, &size, stdin);
  
  while (!WindowShouldClose())
  {
    // Update
    updateSystemState(agents, options.cnt);

    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);
    drawGrid ();
    drawAgents(agents, options.cnt);
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
    agt->my_base.posX = random_range (options.wd_cols);
    agt->my_base.posY = random_range (options.wd_rows);
    agt->my_base.ID = cnt + 1;
    agt->my_base.heading = getRandomDirection ();

    agt->perceptual_radius = 20;
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
 * Draw agents array 'AGENTS' of count 'options.cnt' to winow
 */
static void drawAgents(struct agent *agents, size_t cnt)
{
  while (cnt--)
  {
    struct agent *agt = &agents[cnt];
    int size = options.cell_size; 
    DrawRectangle(agt->my_base.posX * options.cell_size, agt->my_base.posY * options.cell_size, size, size, BLACK);
  }
}

/*
 * Draw A grid  
*/
static void drawGrid (void)
{

  for (int col = 0; col < options.wd_cols; col++)
  {
    for (int row = 0; row < options.wd_rows; row++)
    {
     DrawRectangleLines (col * options.cell_size, row * options.cell_size, options.cell_size, options.cell_size, BLACK);
    }
  }
}