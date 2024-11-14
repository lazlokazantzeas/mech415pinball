#include <iostream>
#include <cstdio>
#include <cmath>
#include <Windows.h> // also needed for the 2D graphics library
#include "2D_graphics.h" // use the 2D graphics library
#include "timer.h" // use the time / clock reading function
#include "Ball.h" // pinball position and trajectory
#include "Collisions.h" // Collision related functions
#include "Stage.h"
#include "Circle Drawing.h"

using namespace std;


// this program tests the ball and collision features on a 600 wide by 800 tall screen 

int main()
{
	
	initialize_graphics();

	Ball ball(400, 300, 350, 250, 25); // Create a ball
	// ball(x_initial, y_initial, vx_initial, vy_initial, r)
	
	double deltaTime = 1.0/60.0; // define timestep to be equal to time per frame

	int id_ball{};
	double theta = 0;
	double scale = 1.0;

	create_sprite("green_circle.png", id_ball); // green circle .png must be in project directory duh


	while (1) {  // Main game loop infinite loop for test

		clear();

		draw_background();
		draw_stage();

		triangleStage t1(265-100, 100, 50, 100, 50, 200); // x1,y1,x2,y2,x3,y3
		triangleStage t2(265+100, 100, 480, 100, 480, 200);
		circleStage c1(265-140, 650, 20, 35); // center x, y, number points, radius
		circleStage c2(265+140, 650, 20, 35);
		circleStage c3(265, 500, 20, 35);

		ball.update(deltaTime); // Update the ball's position

		boundaryCollision(ball, 600, 800); // Handle wall collisions

		draw_sprite(id_ball, ball.x, ball.y, theta, scale); // Sprite takes in ball coordinates


		update();
	}
	
		
	cout << "\ndone.\n";
	getchar();

	return 0;
}