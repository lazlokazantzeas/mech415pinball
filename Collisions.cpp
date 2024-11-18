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
	// square of the magnitude of lines between centers, don't need to sqrt yet, especially seeing as it is slow
	double mag_squared = ((ball.x - circle.cx) * (ball.x - circle.cx) + (ball.y - circle.cy) * (ball.y - circle.cy));
	
	// testing if ball is touching circular stage element by comparing distance between centers to sum of radii
	if (mag_squared < ((ball.radius + circle.rad) * (ball.radius + circle.rad))) {
	
		//cout << 1 << endl; // testing if statement
		
		double mag = sqrt(mag_squared);

		// finding overlap between circles
		double overlap = 0.5 * (mag - (ball.radius + circle.rad));

		// finding normal vector at surface, unitized vector that connects circle centers
		double normal_x = (ball.x - circle.cx) / mag;
		double normal_y = (ball.y - circle.cy) / mag;

		// displacing balls to be tangent if they would overlap, prevents conditions where ball gets stuck inside stage
		ball.x -= (overlap * normal_x);
		ball.y -= (overlap * normal_y);
		
		// taking dot product of vector with the normal 
		double dpNormal = ball.vx * normal_x + ball.vy * normal_y;
		
		// ball retains velocity tangential to surface (dp = dot product = 0)
		// ball reverses direction in the normal direction: 
		// dp "squishes" vector into n,t space
		// then negative 2x reverses direction of velocity vector (normal component only)
		// normal projects it back into x,y-space
		ball.vx = ball.vx - 2 * (dpNormal) * normal_x;
		ball.vy = ball.vy - 2 * (dpNormal) * normal_y;
	}
}