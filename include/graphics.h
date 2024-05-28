
struct masf_options {
  int initialized;
  int wd_rows;
  int wd_cols;
  int center_x;
  int center_y;
  int cnt;
  int cell_size;
  int screen_width;
  int screen_height;
  int fps;
};

struct masf_options agent_init (struct masf_options *settings);
int agent_setattr (struct masf_options new_options);

void start_sim(void);