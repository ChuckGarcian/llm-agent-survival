/* Underlying World Data */
#define WD_ROWS 200
#define WD_COLS 350
#define CENTER_X WD_COLS / 2
#define CENTER_Y WD_ROWS / 2
#define CNT 500

/* Ralyib Window Data */
#define CELL_SIZE 5
#define SCRNW WD_COLS * CELL_SIZE
#define SRCHT WD_ROWS * CELL_SIZE
#define FPS 20

/* Agent Behavior Function */
void agtClientUpdate(struct agent *agent);