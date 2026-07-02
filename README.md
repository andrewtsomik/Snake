#Snake

Play snake on your Raspberry Pi 4's Pi Hat in two modes, tilt your Pi to move the snake or lay your Pi flat to move the snake with your joystick! 
Pay attention to stdout to see your score but be careful, after 5 losses, the display will turn red and the display will close, terminating your attempt.
If you can fill the display with your snake, you will be met with a triumphant white display and the program will end.

##Theory

The theory behind the joystick movement was simple but we wanted to challenge ourselves by having a secondary input.
I researched the mathematics behind how planes and encorporated pitch and roll.
These quantities were computed as such:
'''
double pitch = atan2(coords.y, sqrt(pow(coords.x, 2) + pow(coords.z, 2))) * 57.29578;

double roll = atan2(coords.x, sqrt(pow(coords.y, 2) + pow(coords.z, 2))) * 57.29578;
'''

The parameters in these equations were obtained by reading data from the accelerometer built into the Raspberry Pi 4 Model B.

##Contributors 

Andrew Tsomik | atsomik@terpmail.umd.edu (no longer atsomik@udel.edu)

Jacob Portale | jportale@udel.edu

##Contributions

Andrew Tsomik:
Built input.c and parts of main.c, debugging

Jacob Portale:
Built output.c and parts of main.c, debugging

##Instructions

1. To clone the repository, git clone git@gitlab:atsomik/cisc210-final
2. Run "make all" and then "./final", or "make run" to compile and run
3. To use the joystick input, Pi must be laying on a flat surface
4. To play the game by tilt, tilt your Pi in the desired direction of movement
5. To reset the game, press down on the joystick
6. The program will end after 5 game attempts but, to quit the program prematurely, enter Ctrl + C
