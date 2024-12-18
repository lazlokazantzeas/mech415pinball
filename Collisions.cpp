// Source code for all collision related functions
#define NOMINMAX
#include "Collisions.h"
#include "Flipper.h"
#include <iostream>
#include <cstdio>
#include <windows.h>
#include <cmath>
#include <algorithm>
#include "Circle Drawing.h"

using namespace std;

const double PI = 3.141592653589793;

bool boundaryCollision(Ball& ball, int screenWidth, int screenHeight) {

	bool bottomcollision = 0;
	
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
		bottomcollision = 1;
		ball.y = 0 + ball.radius;
		ball.vy *= -1.0;  // UNO Reverse Card for Y velocity ... im such a poser i've never played UNO
	}	
	
	if (ball.y + ball.radius > screenHeight) {
		ball.y = screenHeight - ball.radius;
		ball.vy *= -1.0;  // UNO Reverse Card for Y velocity ... im such a poser i've never played UNO
	}
	return bottomcollision;
}

bool circleCollisions(Ball& ball, circleStage& circle) {
	// square of the magnitude of lines between centers, don't need to sqrt yet, especially seeing as it is slow
	double mag_squared = ((ball.x - circle.cx) * (ball.x - circle.cx) + (ball.y - circle.cy) * (ball.y - circle.cy));

	bool circlecollision = 0;
	
	// testing if ball is touching circular stage element by comparing distance between centers to sum of radii
	if (mag_squared < ((ball.radius + circle.rad) * (ball.radius + circle.rad))) {

		circlecollision = 1;
		
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
	return circlecollision;
}



void flipperCollision(Ball& ball, Flipper& flipper, bool pivotAtRight) {
	const double PI = 3.141592653589793;


	double ex, ey;
	if (pivotAtRight) {
		ex = flipper.px - flipper.length * cos(-flipper.angle * PI / 180.0);
		ey = flipper.py + flipper.length * sin(-flipper.angle * PI / 180.0);
	}
	else {
		ex = flipper.px + flipper.length * cos(flipper.angle * PI / 180.0);
		ey = flipper.py - flipper.length * sin(flipper.angle * PI / 180.0);
	}


	double fx = ex - flipper.px;
	double fy = ey - flipper.py;
	double flipperLengthSquared = fx * fx + fy * fy;

	// Project ball center onto flipper line
	double t = ((ball.x - flipper.px) * fx + (ball.y - flipper.py) * fy) / flipperLengthSquared;
	t = max(0.0, min(1.0, t));

	// Closest point on flipper
	double closestX = flipper.px + t * fx;
	double closestY = flipper.py + t * fy;

	// Vect closest point to ball
	double distX = ball.x - closestX;
	double distY = ball.y - closestY;
	double distance = sqrt(distX * distX + distY * distY);

	if (distance < ball.radius) {
		// Resolve overlap
		double overlap = ball.radius - distance;
		ball.x += (overlap * distX) / distance;
		ball.y += (overlap * distY) / distance;

		// Calculate and normal vector
		double normalX = distX / distance;
		double normalY = distY / distance;

		// Uno reverse card
		double dotProduct = ball.vx * normalX + ball.vy * normalY;
		ball.vx -= 2 * dotProduct * normalX;
		ball.vy -= 2 * dotProduct * normalY;



		// Debug
		circle_creator(closestX, closestY, 20, 5.0);
	}
}

// this function allows the ball to get out of its initial channel once it hits the 
// top right corner triangle
void initialCollision(Ball& ball) {
	
	if ((ball.y > 750) && (ball.x > 550)) {

		ball.y = 750;

		ball.vx = - 750.0;
		ball.vy *= - 1.0;
	}
}

// this function prevents the ball to go through the wall on the right hand side
void stageCollisions(Ball& ball) {
	
	if ((ball.x + ball.radius > 530) && (ball.x + ball.radius < 550) && 
		(ball.y - ball.radius < 700)) {
		
		ball.x = 530 - ball.radius;
		ball.vx *= -1.0;
	}
}
