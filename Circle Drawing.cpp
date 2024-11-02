
#include <iostream>
#include <cstdio>
#include <cmath>

#include <Windows.h> // also needed for the 2D graphics library

#include "2D_graphics.h" // use the 2D graphics library

#include "timer.h" // use the time / clock reading function

using namespace std;

void draw_background();
void circle_creator(double x[], double y[], int n, int r);
const double PI = 4 * atan(1);
const int cx = 300, cy = 400;

int main()
{
	initialize_graphics();
	
	double r{1}, g{}, b{};
	const int n{20+1};
	int rad{150};

	double circle_y[n];
	double circle_x[n];
	
	clear();

	draw_background();

	circle_creator(circle_x, circle_y, n, rad);

	line(circle_x, circle_y, n, r, g, b);

	update();

	cout << "\ndone.\n";
	getchar();

	return 0;
}

void draw_background() {
	double r[3] = {}, g[3] = {}, b[3] = {};
	double background_x1[3] = { 0,0,600 };
	double background_y1[3] = { 0,800,800 };
	double background_x2[3] = { 0,600,600 };
	double background_y2[3] = { 0,800,0 };

	triangle(background_x1, background_y1, r, g, b);
	triangle(background_x2, background_y2, r, g, b);
}

void circle_creator(double x[], double y[], int n, int r) {
	int i{};

	for (i = 0; i < n; i++) {
		x[i] = cx + (r * cos(2 * PI * ((double)i / (n - 1))));
		// cout << i << "\t" << x[i] << "\n";
	}

	for (i = 0; i < n; i++) {
		y[i] = cy + (r * sin(2 * PI * ((double)i / (n - 1))));
		// cout << i << "\t" << y[i] << "\n";
	}

}