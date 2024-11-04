#include "Stage.h"
#include <Windows.h> // also needed for the 2D graphics library
#include "2D_graphics.h" // use the 2D graphics library
#include "timer.h" // use the time / clock reading function

// Draws a black background
void draw_background() {

	// setting colours
	double r[3] = {}, g[3] = {}, b[3] = {};

	// setting coordinates 
	double background_x1[3] = { 0,0,600 };
	double background_y1[3] = { 0,800,800 };
	double background_x2[3] = { 0,600,600 };
	double background_y2[3] = { 0,800,0 };

	triangle(background_x1, background_y1, r, g, b);
	triangle(background_x2, background_y2, r, g, b);
}

// creates the lines that represent the stage
void draw_stage() {

	const int n{ 10 };
	int r{ 1 }, g{}, b{};

	// draws outline for level, following borders with little launch track on the side
	double stage_x[n] = { 0,550,550,525,525,599,599,550,0,0 };
	double stage_y[n] = { 0,0,700,700,0,0,750,799,799,0 };
	line(stage_x, stage_y, n, r, g, b);
}

