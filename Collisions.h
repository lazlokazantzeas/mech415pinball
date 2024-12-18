#pragma once
#include "Ball.h"
#include "Stage.h"
#include "Flipper.h"

//function prototype for boundary (exterior wall) collisions
void boundaryCollision(Ball& ball, int screenWidth, int screenHeight);

void circleCollisions(Ball& ball, circleStage& circle);

// function prototype for collisions with the flippers
void flipperCollision(Ball& ball, Flipper& flipper, bool pivotAtRight);