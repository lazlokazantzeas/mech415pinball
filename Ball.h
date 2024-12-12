//Ball.h 

#pragma once

class Ball {
public:
	double x, y;          // position of the ball
	double vx, vy;        // velocity of the ball
	double ax, ay;		  // acceleration of the ball
	double radius;        // radius of the ball/sprite/circle object

	Ball(double x_initial, double y_initial, double vx_initial, double vy_initial, double r);

	void update(float deltaTime);

};

// the car is on fire....
// and there's no driver at the wheel...
// the sewers are muddied with a thousand lonely suicides
// and a dark wind blows
// the government is corrupt
// and we're on so many drugs with the curtains drawn 
// and the radios on
// we're trapped in the belly of their horribly machine
// and the machine is bleeding to death
//
// 
