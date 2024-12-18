//Ball.h 

#pragma once

class Ball {
public:
	double x, y;          // position of the ball
	double vx, vy;        // velocity of the ball
	double ax, ay;		  // acceleration of the ball
	double radius;        // radius of the ball/sprite/circle object
	bool kicked;			// prevent repeated kicks

	Ball(double x_initial, double y_initial, double vx_initial, double vy_initial, double r);

	void update(double deltaTime);

};


