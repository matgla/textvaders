/*
 Copyright (c) 2025 Mateusz Stadnik

 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

// #include <stdio.h>
// #include <unistd.h>

// #include <ncurses.h>

// #define WINDOW_WIDTH 80
// #define WINDOW_HEIGHT 24
// #define MAX_MISSILES 3
// #define MAX_ENEMIES 50

// typedef enum { EMPTY, MISSILE, WALL, PLAYER, ENEMY, ITEM } object_type;

// typedef enum EDirection {
//   EDirection_Left = 1,
//   EDirection_Right = 2,
// } EDirection;

// typedef struct object {
//   int type;
//   int x;
//   int y;
//   int variant;
// } object;

// void init_colors(void) {
//   start_color();
//   init_pair(1, COLOR_GREEN, COLOR_BLACK);
//   init_pair(2, COLOR_CYAN, COLOR_BLACK);
//   init_pair(3, COLOR_YELLOW, COLOR_BLACK);
//   init_pair(4, COLOR_RED, COLOR_BLACK);
//   init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
//   init_pair(6, COLOR_BLUE, COLOR_BLACK);
// }

// WINDOW *create_window(int height, int width, int start_y, int start_x) {
//   WINDOW *win = newwin(height, width, start_y, start_x);
//   box(win, '|', '-');
//   wrefresh(win);
//   return win;
// }

// void delete_player(WINDOW *win, object *player) {
//   mvwaddch(win, player->y, player->x, ' ');
//   mvwaddch(win, player->y, player->x + 1, ' ');
//   mvwaddch(win, player->y, player->x + 2, ' ');
//   mvwaddch(win, player->y - 1, player->x + 1, ' ');
// }

// void display_player(WINDOW *win, object *player) {
//   wattron(win, COLOR_PAIR(1));
//   mvwaddch(win, player->y, player->x, '#');
//   mvwaddch(win, player->y, player->x + 1, '#');
//   mvwaddch(win, player->y, player->x + 2, '#');
//   mvwaddch(win, player->y - 1, player->x + 1, '#');
//   wattroff(win, COLOR_PAIR(1));
// }

// void update_missile(WINDOW *win, object *missile) {
//   mvwaddch(win, missile->y, missile->x, ' ');
//   missile->y--;
//   mvwaddch(win, missile->y, missile->x, '*');
// }
// void delete_missile(WINDOW *win, object *missile) {
//   mvwaddch(win, missile->y, missile->x, ' ');
// }

// void delete_enemy(WINDOW *win, object *enemy) {
//   mvwaddch(win, enemy->y - 1, enemy->x + 1, ' ');
//   mvwaddch(win, enemy->y, enemy->x, ' ');
//   mvwaddch(win, enemy->y, enemy->x + 2, ' ');
// }

// void display_enemy(WINDOW *win, object *enemy) {
//   wattron(win, COLOR_PAIR(3));
//   mvwaddch(win, enemy->y - 1, enemy->x + 1, 'o');
//   if (enemy->variant == 0) {
//     mvwaddch(win, enemy->y, enemy->x, '\\');
//     mvwaddch(win, enemy->y, enemy->x + 2, '/');
//     enemy->variant = 1;
//   } else {
//     mvwaddch(win, enemy->y, enemy->x, '/');
//     mvwaddch(win, enemy->y, enemy->x + 2, '\\');
//     enemy->variant = 0;
//   }
//   wattroff(win, COLOR_PAIR(3));
// }
// void move_player(WINDOW *win, object *player, EDirection direction) {
//   delete_player(win, player);
//   if (direction == EDirection_Left) {
//     if (player->x > 2) {
//       player->x--;
//     }
//   } else if (direction == EDirection_Right) {
//     if (player->x < WINDOW_WIDTH - 4) {
//       player->x++;
//     }
//   }
//   display_player(win, player);
// }

// void shoot(WINDOW *win, object *player, object *missiles) {
//   for (int i = 0; i < MAX_MISSILES; i++) {
//     if (missiles[i].type == EMPTY) {
//       missiles[i].type = MISSILE;
//       missiles[i].x = player->x + 1;
//       missiles[i].y = player->y - 1;
//       break;
//     }
//   }
// }

// int prepare_enemies(object *enemies) {
//   for (int i = 0; i < MAX_ENEMIES; i++) {
//     enemies[i].type = EMPTY;
//     enemies[i].x = 0;
//     enemies[i].y = 0;
//     enemies[i].variant = 0;
//   }

//   for (int i = 0; i < 10; i++) {
//     enemies[i].type = ENEMY;
//     enemies[i].x = i * 6 + 6;
//     enemies[i].y = 4;
//   }

//   for (int i = 0; i < 10; i++) {
//     enemies[i + 10].type = ENEMY;
//     enemies[i + 10].x = i * 6 + 10;
//     enemies[i + 10].y = 6;
//   }
//   for (int i = 0; i < 10; i++) {
//     enemies[i + 20].type = ENEMY;
//     enemies[i + 20].x = i * 6 + 6;
//     enemies[i + 20].y = 8;
//   }
//   return 30;
// }

// int check_collision(WINDOW *win, object *missile, object *enemies) {
//   for (int i = 0; i < MAX_ENEMIES; i++) {
//     if (enemies[i].type == EMPTY)
//       continue;
//     if ((missile->x == enemies[i].x + 1 && missile->y == enemies[i].y - 1) ||
//         (missile->x == enemies[i].x && missile->y == enemies[i].y) ||
//         (missile->x == enemies[i].x + 2 && missile->y == enemies[i].y)) {
//       delete_missile(win, missile);
//       missile->type = EMPTY;
//       delete_enemy(win, &enemies[i]);
//       enemies[i].type = EMPTY;
//       return 1;
//     }
//   }
//   return 0;
// }

// int main() {
//   int ch;
//   initscr();
//   cbreak();
//   noecho();
//   nodelay(stdscr, TRUE);
//   keypad(stdscr, TRUE);
//   curs_set(0);
//   init_colors();
//   int height = WINDOW_HEIGHT;
//   int width = WINDOW_WIDTH;
//   int start_y = height / 2;
//   int start_x = width / 2;
//   int missile_delay = 0;
//   int enemy_delay = 0;
//   int score = 0;
//   refresh();

//   object player = {PLAYER, WINDOW_WIDTH / 2, WINDOW_HEIGHT - 3};
//   object missiles[3] = {{EMPTY, 0, 0}, {EMPTY, 0, 0}, {EMPTY, 0, 0}};
//   object enemies[MAX_ENEMIES] = {};
//   int enemies_number = prepare_enemies(enemies);
//   EDirection enemies_direction = EDirection_Right;
//   EDirection new_direction = enemies_direction;
//   WINDOW *win = create_window(height, width, start_y, start_x);
//   int enemies_delay = 20;
//   int game_finished = 0;
//   while ((ch = getch()) != 'q') {
//     if (game_finished)
//       continue;
//     switch (ch) {
//     case KEY_LEFT:
//       move_player(win, &player, EDirection_Left);
//       break;
//     case KEY_RIGHT:
//       move_player(win, &player, EDirection_Right);
//       break;
//     case ' ':
//       shoot(win, &player, missiles);
//       break;
//     }

//     if (enemies_number == 0) {
//       enemies_number = prepare_enemies(enemies);
//       enemies_delay -= 2;
//       if (enemies_delay == 20) {
//         // you won
//         mvwprintw(win, WINDOW_HEIGHT / 2 - 1, (WINDOW_WIDTH - 10) / 2,
//                   "You won!");
//         mvwprintw(win, WINDOW_HEIGHT / 2, (WINDOW_WIDTH - 10) / 2,
//                   "Your score: %d", score);
//         mvwprintw(win, WINDOW_HEIGHT / 2 + 1, (WINDOW_WIDTH - 10) / 2,
//                   "Press q to exit");
//         wrefresh(win);
//         game_finished = 1;
//       }
//     }

//     if (missile_delay++ % 5 == 0) {
//       for (int i = 0; i < 3; i++) {
//         if (missiles[i].type == MISSILE) {
//           if (missiles[i].y > 2) {
//             update_missile(win, &missiles[i]);
//             if (check_collision(win, &missiles[i], enemies)) {
//               enemies_number--;
//               score += 10;
//             }
//           } else {
//             delete_missile(win, &missiles[i]);
//             missiles[i].type = EMPTY;
//           }
//         }
//       }
//     }

//     if (enemy_delay++ % enemies_delay == 0) {
//       int direction_changed = 0;
//       if (new_direction != enemies_direction) {
//         enemies_direction = new_direction;
//         direction_changed = 1;
//       }
//       for (int i = 0; i < MAX_ENEMIES; i++) {
//         if (enemies[i].type == ENEMY) {
//           delete_enemy(win, &enemies[i]);
//           if (direction_changed) {
//             enemies[i].y++;
//             if (enemies[i].y > WINDOW_HEIGHT - 4) {
//               // you lost
//               mvwprintw(win, WINDOW_HEIGHT / 2 - 1, (WINDOW_WIDTH - 10) / 2,
//                         "You lost!");
//               mvwprintw(win, WINDOW_HEIGHT / 2, (WINDOW_WIDTH - 10) / 2,
//                         "Your score: %d", score);
//               mvwprintw(win, WINDOW_HEIGHT / 2 + 1, (WINDOW_WIDTH - 10) / 2,
//                         "Press q to exit");
//               wrefresh(win);
//               game_finished = 1;
//             }
//           }
//           if (enemies_direction == EDirection_Right) {
//             enemies[i].x++;
//             if (enemies[i].x > width - 6) {
//               new_direction = EDirection_Left;
//             }
//           } else {
//             enemies[i].x--;
//             if (enemies[i].x < 4) {
//               new_direction = EDirection_Right;
//             }
//           }
//           display_enemy(win, &enemies[i]);
//         }
//       }
//     }

//     mvwprintw(win, 0, 1, "Score: %d", score);
//     display_player(win, &player);
//     wrefresh(win);
//     napms(10);
//   }
//   endwin();
//   return 0;
// }

#include <stdio.h>

#define TOK_IDENT 256

int print(int c, char *ch) {
  printf("%d : ch: %d\n", c, *ch);
  return c;
}

int main() {
  char c = '<';
  print(c == '<' ? '>' : c, &c);
  return 0;
}