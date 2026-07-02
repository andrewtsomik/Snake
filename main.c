#include "project.h"

int main(void){
	open_display();
	open_input();
	Game game;
	int tries = 0;
	int previous_running = 1;
	printf("You get 5 tries.\n");
	init_game(&game);

	while(tries < 5){
		check_input(&game);
    		if(game.running){
			previous_running = 1;
        		continue_game(&game);
        		if(game.running){
            			change_snake(&game);
        		}
    		
			if(game.score == 64){
				game.running = 0;
				display_win();
				printf("Congratulations! You win!!!\n");
				sleep(3);
				clear_display();
				close_input();
				close_display();
				return 0;
			}
    			display_game(&game);
		}
		else{

			if (previous_running){
				tries++;
				previous_running = 0;
				if (tries != 5){
					printf("Try again.\n");
				}
			}
		}
		usleep(200000);
	}
	display_loss();
	printf("You lose.\n");
	sleep(3);
	clear_display();
	close_input();
	close_display();
	return 0;
}
