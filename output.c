#include "project.h"


pi_framebuffer_t *fb = NULL;

void open_display(void){
    if (fb != NULL){
        return;
    }
    fb = getFrameBuffer();
}
void clear_display(void){	
        clearFrameBuffer(fb,BLACK);
}


void display_pixel(int x, int y, uint16_t color){
	sense_fb_bitmap_t *bm=fb->bitmap;
	bm->pixel[x][y] = color;
}

void display_game(Game *game){
	clear_display();
	display_pixel(game->Apple.x, game->Apple.y, RED);
	for (int i = 0; i < game->length; i++){
		display_pixel(game->snake[i].x, game->snake[i].y, GREEN);
	}
}

void display_win(void){
	clear_display();
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			display_pixel(i, j, WHITE);
		}
	}
}

void display_loss(void){
	clear_display();
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			display_pixel(i, j, RED);
		}
	}
}


void rand_apple(Game *game){
	int collision;
	do {
		collision = 0;
		game->Apple.x = rand() % 8;
		game->Apple.y = rand() % 8;
		for(int i = 0; i < game->length; i++){
			if(game->snake[i].x == game->Apple.x && game->snake[i].y == game->Apple.y){
				collision = 1;
				break;
			}
		}
	}while(collision);
}


int ate_apple(Game *game){
	if (game->snake[game->length - 1].x == game->Apple.x &&
	    game->snake[game->length - 1].y == game->Apple.y){
		return 1;
	}
	else{
		return 0;
	}
}

void init_game(Game *game){
    game->length = 3;

    game->snake[0].x = 0;
    game->snake[0].y = 4;

    game->snake[1].x = 1;
    game->snake[1].y = 4;

    game->snake[2].x = 2;
    game->snake[2].y = 4;

    game->facing = RIGHT;

    game->score = 0;

    game->running = 1;

    rand_apple(game);
}

void change_snake(Game *game){
	int new_head_index;
	int ate = ate_apple(game);
	if (ate){
		new_head_index = game->length;
		game->length++;
	}
	else{
		for (int i = 0; i < game->length - 1; i++){
			game->snake[i] = game->snake[i+1];
		}
		new_head_index = game->length - 1;
	}	
	if (game->facing == UP){
		game->snake[new_head_index].x = game->snake[new_head_index - 1].x;
		game->snake[new_head_index].y = game->snake[new_head_index - 1].y + 1;
	}
	else if (game->facing == DOWN){
		game->snake[new_head_index].x = game->snake[new_head_index - 1].x;
		game->snake[new_head_index].y = game->snake[new_head_index - 1].y - 1;
	}
	else if (game->facing == RIGHT){
		game->snake[new_head_index].x = game->snake[new_head_index - 1].x + 1;
		game->snake[new_head_index].y = game->snake[new_head_index - 1].y;
	}
	else if (game->facing == LEFT){
		game->snake[new_head_index].x = game->snake[new_head_index - 1].x - 1;
		game->snake[new_head_index].y = game->snake[new_head_index - 1].y;
	}
	if (ate){
		game->score++;
		printf("Score: %d\n", game->score);
		rand_apple(game);
	}
}

void continue_game(Game *game){
	for (int i = 0; i < game->length - 1; i++){
		if (game->snake[i].x == game->snake[game->length - 1].x &&
		    game->snake[i].y == game->snake[game->length - 1].y){
			game->running = 0;
		}
	}
	if (game->facing == UP){
		if (game->snake[game->length - 1].y == 7){
			game->running = 0;
		}
	}
	else if (game->facing == DOWN){
		if (game->snake[game->length - 1].y == 0){
			game->running = 0;
		}
	}
	else if (game->facing == RIGHT){
		if (game->snake[game->length - 1].x == 7){
			game->running = 0;
		}
	}
	else if (game->facing == LEFT){
		if (game->snake[game->length - 1].x == 0){
			game->running = 0;
		}
	}
}


void close_display(void){
    if (fb != NULL){
        clear_display();
        sleep(1);
        freeFrameBuffer(fb);
        fb = NULL;
    }
}

