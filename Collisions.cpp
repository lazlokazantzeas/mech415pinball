// Source code for all collision related functions

#include "Collisions.h"

void boundaryCollision(Ball& ball, int screenWidth, int screenHeight) {

	// Side Walls
	if (ball.x - ball.radius < 0) {
		ball.x = 0 + ball.radius; // this fixes a bug, the ball now cannot become infinitely stuck in the wall if it enters with sufficient speed
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
