//Ball.h 

#pragma once

class Ball {
public:
	double x, y;          // position of the ball
	double vx, vy;        // velocity of the ball
	double radius;        // radius of the ball/sprite/circle object

	Ball(double x_initial, double y_initial, double vx_initial, double vy_initial, double r);

	void update(float deltaTime);

};

// the car is on fire....
// and there's no driver at the wheel...