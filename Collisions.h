#pragma once
#include "Ball.h"
#include "Stage.h"
#include "Flipper.h"

//function prototype for boundary (exterior wall) collisions
bool boundaryCollision(Ball& ball, int screenWidth, int screenHeight);

bool circleCollisions(Ball& ball, circleStage& circle);

// function prototype for collisions with the flippers
void flipperCollision(Ball& ball, Flipper& flipper, bool pivotAtRight);

void initialCollision(Ball& ball);

void stageCollisions(Ball& ball);
