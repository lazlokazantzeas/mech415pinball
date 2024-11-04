#include <cstdio>
#include <cmath>
#include <Windows.h> // also needed for the 2D graphics library
#include "2D_graphics.h" // use the 2D graphics library
#include "timer.h" // use the time / clock reading function
#include "Circle Drawing.h"

using namespace std;

const double PI = 4 * atan(1);

void circle_creator(int cx, int cy, int n, int r) {
	int i{};
	n += 1; // need an extra point for start and endpoints to meet
	
	// dynamic arrays for all points of circle
	double* x; 
	double* y;
	x = new double[n];
	y = new double[n];
	
	// colour of circle, should probably have all stage elements standardized
	int rb{ 1 }, gb{}, bb{};

	// generating x and y coordinates for each of the n+1 points 
	for (i = 0; i < n; i++) {
		x[i] = cx + (r * cos(2 * PI * ((double)i / (n - 1))));
		y[i] = cy + (r * sin(2 * PI * ((double)i / (n - 1))));
		//cout << i << "\t" << x[i] << "\n";
		//cout << i << "\t" << y[i] << "\n";
	}

	line(x, y, n, rb, gb, bb);

}