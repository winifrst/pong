#include <stdio.h>
#define WIDTH 80
#define HEIGHT 25

void draw(char control, int frst_pos, int scnd_pos, int ball_x, int ball_y,
          int score_frst, int score_scnd);
int rack_pos_frst(int frst_pos, char control);
int rack_pos_scnd(int frst_scnd, char control);
void winner(int score_frst, int score_scnd);

int main() {
  int frst_pos = HEIGHT / 2;
  int scnd_pos = HEIGHT / 2;
  int ball_x = WIDTH / 2;
  int ball_y = HEIGHT / 2;
  int dir_x = 1;
  int dir_y = 1;
  int score_frst = 0, score_scnd = 0;
  char control = 0;

  draw(control, frst_pos, scnd_pos, ball_x, ball_y, score_frst, score_scnd);

  while (score_frst < 21 && score_scnd < 21) {
    while ((control = getchar()) != '\n') {
      if (ball_x == 2 && (ball_y >= frst_pos - 1 && ball_y <= frst_pos + 1)) {
        dir_x = 1;
      }
      if (ball_x == WIDTH - 3 && ball_y >= scnd_pos - 1 &&
          ball_y <= scnd_pos + 1) {
        dir_x = -1;
      }
      ball_x += dir_x;
      
      if (ball_y == HEIGHT - 2) {
        dir_y = -1;
      }
      if (ball_y == 1) {
        dir_y = 1;
      }
      ball_y += dir_y;

      frst_pos = rack_pos_frst(frst_pos, control);
      scnd_pos = rack_pos_scnd(scnd_pos, control);

      draw(control, frst_pos, scnd_pos, ball_x, ball_y, score_frst, score_scnd);

      if (ball_x == 1) {
        score_scnd++;
        ball_x = WIDTH / 2;
        ball_y = HEIGHT / 2;
      }
      if (ball_x == WIDTH - 2) {
        score_frst++;
        ball_x = WIDTH / 2;
        ball_y = HEIGHT / 2;
      }
    }
  }
  winner(score_frst, score_scnd);
  return 0;
}

void draw(char control, int frst_pos, int scnd_pos, int ball_x, int ball_y,
          int score_frst, int score_scnd) {
  int field[HEIGHT][WIDTH];
  printf("\033[0d\033[2J");
  printf("%d - %d\n", score_frst, score_scnd);
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      if (y == 0 || y == HEIGHT - 1) {
        printf("=");
      } else if (x == 0 || x == WIDTH - 1) {
        printf("|");
      } else if (((x == 1 && (y <= (frst_pos) + 1 && y >= (frst_pos)-1))) ||
                 (x == WIDTH - 2 &&
                  ((y <= (scnd_pos) + 1 && y >= (scnd_pos)-1)))) {
        printf("I");
      } else if (x == ball_x && y == ball_y) {
        printf("o");
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
}

int rack_pos_frst(int frst_pos, char control) {
  if (control == 'a' && frst_pos > 2) {
    (frst_pos)--;
  }
  if (control == 'z' && frst_pos < HEIGHT - 3) {
    (frst_pos)++;
  }
  return frst_pos;
}

int rack_pos_scnd(int scnd_pos, char control) {
  if (control == 'k' && scnd_pos > 2) {
    (scnd_pos)--;
  }
  if (control == 'm' && scnd_pos < HEIGHT - 3) {
    (scnd_pos)++;
  }
  return scnd_pos;
}

void winner(int score_frst, int score_scnd) {
  printf("\033[0d\033[2J");
  (score_frst > score_scnd) ? printf("===== FIRST PLAYER WON =====")
                            : printf("===== SECOND PLAYER WON =====");
}
