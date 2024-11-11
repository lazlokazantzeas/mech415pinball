// a class to 
#include "Ball.h"



	Ball::Ball(double x_initial, double y_initial, double vx_initial, double vy_initial, double r) {
		
		x = x_initial;
		y = y_initial;
		vx = vx_initial;
		vy = vy_initial;
		ax = 0;
		ay = -250;
		radius = r;
		
	}


	void Ball::update(float deltaTime) {
		
		vx += ax * deltaTime;
		x += vx * deltaTime;

		vy += ay * deltaTime;
		y += vy * deltaTime;

	}