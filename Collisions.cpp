// Source code for all collision related functions

#include "Collisions.h"

void boundaryCollision(Ball& ball, int screenWidth, int screenHeight) {

	// Side Walls
	if (ball.x - ball.radius < 0 || ball.x + ball.radius > screenWidth) {
		ball.vx *= -1;  // UNO Reverse card for X velocity
	}
	// Top and bottom walls
	if (ball.y - ball.radius < 0 || ball.y + ball.radius > screenHeight) {
		ball.vy *= -1;  // UNO Reverse Card for Y velocity ... im such a poser i've never played UNO
	}

}