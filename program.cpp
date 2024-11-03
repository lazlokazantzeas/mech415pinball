
#include <iostream>
#include <cstdio>
#include <cmath>
#include <Windows.h> // also needed for the 2D graphics library
#include "2D_graphics.h" // use the 2D graphics library
#include "timer.h" // use the time / clock reading function
#include "Ball.h" // pinball position and trajectory
#include "Collisions.h" // Collision related functions

using namespace std;


// this program tests the ball and collision features on a 800 wide by 600 tall screen 



int main()
{
	
	initialize_graphics();

	Ball ball(400, 300, 200, 175, 25); // Create a ball
	
	double deltaTime = 0.016; // 

	int id_ball;
	double theta = 0;
	double scale = 1.0;

	create_sprite("green_circle.png", id_ball); // green circle .png must be in project directory duh

	while (1) {  // Main game loop infinite loop for test

		clear();

		ball.update(deltaTime); // Update the ball's position

		boundaryCollision(ball, 800, 600); // Handle wall collisions

		draw_sprite(id_ball, ball.x, ball.y, theta, scale); // Sprite takes in ball coordinates

		update();
	}
	
	
	cout << "\ndone.\n";
	getchar();

	return 0;
}

