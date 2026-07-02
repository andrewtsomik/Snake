#include "project.h"

pi_joystick_t *joystick = NULL;
pi_i2c_t *device = NULL;
Game *current_game = NULL;

void open_input(void) {
    if (joystick == NULL) {
        joystick = getJoystickDevice();
    }
    if(device == NULL){
    	device = geti2cDevice();
	configureAccelGyro(device);
    }
}

void close_input(void) {
    if (joystick != NULL) {
        freeJoystick(joystick);
        joystick = NULL;
    }
    if (device != NULL){
    	freei2cDevice(device);
	device = NULL;
    }
}

void check_joystick(Game *game){
    current_game = game;
    pollJoystick(joystick, joystick_callback, 0);

}

void joystick_callback(unsigned int code){
    if(current_game == NULL)
	    return;
    Game *game = current_game;
        if(code == KEY_RIGHT && game->facing != DOWN){
            game->facing = UP;
        }
        else if(code == KEY_LEFT && game->facing != UP){
            game->facing = DOWN;
        }
        else if(code == KEY_DOWN && game->facing != LEFT){
            game->facing = RIGHT;
        }
        else if(code == KEY_UP && game->facing != RIGHT){
            game->facing = LEFT;
        }
        else if(code == KEY_ENTER && game->running == 0){
            init_game(game);
        }
}

void check_accel(Game *game){
    coordinate_t coords;
    if(getAccelData(device, &coords)){
        double pitch = atan2(coords.y,
            sqrt(pow(coords.x, 2) + pow(coords.z, 2))) * 57.29578;

        double roll = atan2(coords.x,
            sqrt(pow(coords.y, 2) + pow(coords.z, 2))) * 57.29578;

    if(fabs(pitch) > fabs(roll)){
    	if(pitch > 15 && game->facing != RIGHT){
        	game->facing = LEFT;
    	}
    	else if(pitch < -15 && game->facing != LEFT){
        	game->facing = RIGHT;
    	}
    }
    else{
    	if(roll > 15 && game->facing != UP){
        	game->facing = DOWN;
    	}
    	else if(roll < -15 && game->facing != DOWN){
        	game->facing = UP;
    	}
	}
    }
}

void check_input(Game *game){
    check_joystick(game);
    check_accel(game);
}
