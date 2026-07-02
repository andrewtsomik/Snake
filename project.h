#ifndef PROJECT_H
#define PROJECT_H
#define _GNU_SOURCE
#include "sense.h"
#include <stdlib.h>
#include <linux/input.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#define WHITE 0xFFFF
#define BLACK 0x0000
#define RED 0xF800
#define GREEN 0x07E0

#define MAX_SNAKE_LEN 64

typedef enum{
	UP, DOWN, LEFT, RIGHT
}Direction;

typedef struct{
	int x;
	int y;
} Location;

typedef struct{
	Location snake[MAX_SNAKE_LEN];
	int length;
	Direction facing;
	Location Apple;
	int score;
	int running;
} Game;

void open_input(void);
void close_input(void);
void check_joystick(Game *game);
void joystick_callback(unsigned int code);
void check_accel(Game *game);
void check_input(Game *game);

void open_display(void);
void clear_display(void);
void display_pixel(int x, int y, uint16_t color);
void display_game(Game *game);
void display_win(void);
void display_loss(void);
void rand_apple(Game *game);
int ate_apple(Game *game);
void init_game(Game *game);
void change_snake(Game *game);
void continue_game(Game *game);
void close_display(void);

#endif
