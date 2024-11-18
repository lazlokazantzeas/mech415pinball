#pragma once
#include "Ball.h"
#include "Stage.h"

//function prototype for boundary (exterior wall) collisions
void boundaryCollision(Ball& ball, int screenWidth, int screenHeight);

void circleCollisions(Ball& ball, circleStage& circle);