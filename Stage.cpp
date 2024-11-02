
#include <iostream>
#include <cstdio>
#include <cmath>

#include <Windows.h> // also needed for the 2D graphics library

#include "2D_graphics.h" // use the 2D graphics library

#include "timer.h" // use the time / clock reading function

using namespace std;

int main()
{

	initialize_graphics();

	clear();

	const int n{ 10 };
	double stage_x[n] = { 50,515,515,525,525,550,550,520,50,50 };
	double stage_y[n] = { 50,50,700,700,50,50,720,750,750,50 };
	double r{1}, g{}, b{};
	double background_x1[3] = { 0,0,600 };
	double background_y1[3] = { 0,800,800 };
	double background_x2[3] = { 0,600,600 };
	double background_y2[3] = { 0,800,0 };
	double rb[3] = {}, gb[3] = {}, bb[3] = {};

	clear();

	triangle(background_x1, background_y1, rb, gb, bb);
	triangle(background_x2, background_y2, rb, gb, bb);
	line(stage_x, stage_y, n, r, g, b);

	update();



	cout << "\ndone.\n";
	getchar();

	return 0;
}

