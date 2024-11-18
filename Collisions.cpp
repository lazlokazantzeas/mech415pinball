// Source code for all collision related functions

#include "Collisions.h"
#include <iostream>
#include <cstdio>
#include <windows.h>
#include <cmath>

using namespace std;

void boundaryCollision(Ball& ball, int screenWidth, int screenHeight) {

	// Side Walls
	if (ball.x - ball.radius < 0) {
		ball.x = 0 + ball.radius; // setting the ball position fixes a bug, 
		// the ball now cannot become infinitely stuck in the wall if it enters with sufficient speed
		ball.vx *= -1.0;  // UNO Reverse card for X velocity
	}	

	if (ball.x + ball.radius > screenWidth) {
		ball.x = screenWidth - ball.radius;
		ball.vx *= -1.0;
	}


	// Top and bottom walls
	if (ball.y - ball.radius < 0) {
		ball.y = 0 + ball.radius;
		ball.vy *= -1.0;  // UNO Reverse Card for Y velocity ... im such a poser i've never played UNO
	}	
	
	if (ball.y + ball.radius > screenHeight) {
		ball.y = screenHeight - ball.radius;
		ball.vy *= -1.0;  // UNO Reverse Card for Y velocity ... im such a poser i've never played UNO
	}

}

void circleCollisions(Ball& ball, circleStage& circle) {
	double mag_squared;
	mag_squared = ((ball.x - circle.cx) * (ball.x - circle.cx) + (ball.y - circle.cy) * (ball.y - circle.cy));
	
	// testing if ball is touching circular stage element by comparing distance between centers to sum of radii
	if (mag_squared < ((ball.radius + circle.rad) * (ball.radius + circle.rad))) {
		//cout << 1 << endl; // testing if statement
		double normal_angle;
		normal_angle = atan((ball.y - circle.cy) / (ball.x - circle.cy));
		
	
	}
}