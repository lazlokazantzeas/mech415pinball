// a class to 
#include "Ball.h"



	Ball::Ball(double x_initial, double y_initial, double vx_initial, double vy_initial, double r) {
		
		x = x_initial;
		y = y_initial;
		vx = vx_initial;
		vy = vy_initial;
		ax = 0;
		ay = -750; // may want to build this into constructor? J - left it floaty for now, easier to see collisions
		radius = r;
		kicked = false;
		
	}


	void Ball::update(double deltaTime) {
		
		vx += ax * deltaTime;
		x += vx * deltaTime;

		vy += ay * deltaTime;
		y += vy * deltaTime;

	}