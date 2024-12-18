#include <iostream>
#include <cstdio>
#include <cmath>
#include <Windows.h> // also needed for the 2D graphics library
#include "2D_graphics.h" // use the 2D graphics library
#include "Ball.h" // pinball position and trajectory
#include "Collisions.h" // Collision related functions
#include "Stage.h"
#include "Circle Drawing.h"
#include "Flipper.h"

using namespace std;


// this program tests the ball and collision features on a 600 wide by 800 tall screen 
int main()
{

	initialize_graphics();

	Ball ball(573, 25, 0, 0, 25); // Create a ball
	//Ball ball(150, 350, 0, 0, 25); // Create a ball DEBUG
	// ball(x_initial, y_initial, vx_initial, vy_initial, r)

	double deltaTime = 1.0 / 60.0; // define timestep to be equal to time per frame

	int id_ball{};
	double theta = 0;
	double scale = 1.0;

	int points = 0;

	create_sprite("green_circle.png", id_ball); // green circle .png must be in project directory duh

	// pivot x, pivot y, length, rest angle, max angle, angular speed
	Flipper leftFlipper(49, 200, 175, 45, 45, 10);
	Flipper rightFlipper(480, 200, 175, 45, 45, 10);

	// Print out message for user to know the controls of the game
	cout << "\nPress Space Bar to Start\n";
	cout << "\nUse key M to activate RIGHT flipper";
	cout << "\nUse key Z to activate LEFT flipper";
	cout << "\nPress key R to restart the game\n\n";

	while (1) {  // Main game loop infinite loop for test

		clear();

		draw_background();
		draw_stage();

		// triangle stage elements not used
		//triangleStage t1(265 - 100, 100, 50, 100, 50, 200); // x1,y1,x2,y2,x3,y3
		//triangleStage t2(265 + 100, 100, 480, 100, 480, 200);
		circleStage c1(265 - 140, 625, 20, 35); // center x, y, number points, radius
		circleStage c2(265 + 140, 625, 20, 35);
		circleStage c3(265, 425, 20, 35);

		leftFlipper.update(KEY('Z'), true);
		rightFlipper.update(KEY('M'), true);

		ball.update(deltaTime); // Update the ball's position

		// Check ball collisions with flippers
		flipperCollision(ball, leftFlipper, false);  // Left flipper, pivot at left-most point
		flipperCollision(ball, rightFlipper, true);  // Right flipper, pivot at right-most point// Pivot at right-most point

		initialCollision(ball);
		stageCollisions(ball);

		// Function that launches the ball once the space bar is pressed
		if (KEY(VK_SPACE) && ball.x > 550) {
			ball.vy = 1200;
			ball.ay = -750;
		}

		if (circleCollisions(ball, c1)) {
			points++;
			cout << "Points = " << points << "\n";
		}
		if (circleCollisions(ball, c2)) {
			points++;
			cout << "Points = " << points << "\n";
		}
		if (circleCollisions(ball, c3)) {
			points++;
			cout << "Points = " << points << "\n";
		}

		// Function that ends the game once the the ball touches the lower boundary
		if (boundaryCollision(ball, 600, 800) && ball.x < 550) {
			cout << "\n\n GAME OVER -- FINAL SCORE = " << points;

			ball.vx = 0;
			ball.vy = 0;
			ball.y = 26;
			ball.ay = 0;
		}

		// Function that allows the ball to be reset to its initial position
		if (KEY('R')) {
			ball.x = 574;
			ball.y = 25;
			ball.vx = 0;
			ball.vy = 0;

			points = 0;
		}

		leftFlipper.draw(false);
		rightFlipper.draw(true);
		initialCollision(ball);
		stageCollisions(ball);
		draw_sprite(id_ball, ball.x, ball.y, theta, scale); // Sprite takes in ball coordinates


		update();
	}


	cout << "\ndone.\n";
	getchar();

	return 0;
}
