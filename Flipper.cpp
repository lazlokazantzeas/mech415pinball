#include "Flipper.h"
#include "2D_graphics.h"
#include <cmath>

const double PI = 3.141592653589793;

// Constructor
Flipper::Flipper(double pivot_x, double pivot_y, double len, double rest_ang, double max_ang, double ang_speed) {
    px = pivot_x;
    py = pivot_y;
    length = len;
    restAngle = rest_ang;
    maxAngle = max_ang;
    angularSpeed = ang_speed;
    angle = restAngle;
}

void Flipper::update(bool keyPressed, bool counterClockwise) {
    if (keyPressed) {
        if (counterClockwise) {
            angle -= angularSpeed;
            if (angle < restAngle - maxAngle) angle = restAngle - maxAngle;
        }
        else {
            angle += angularSpeed;
            if (angle > restAngle + maxAngle) angle = restAngle + maxAngle;
        }
    }
    else {
        // Return to resting position
        if (angle < restAngle) angle += angularSpeed; // Move upward
        if (angle > restAngle) angle -= angularSpeed; // Move downward
        if (std::abs(angle - restAngle) < 0.1) angle = restAngle; // Snap to rest
    }
}

void Flipper::draw(bool pivotAtRight) {
    double x1 = px; // Pivot point X
    double y1 = py; // Pivot point Y

    // Calculate the endpoint of the flipper
    double x2, y2;
    const double PI = 3.141592653589793;

    if (pivotAtRight) {
        x2 = px - length * cos(-angle * PI / 180.0);
        y2 = py + length * sin(-angle * PI / 180.0);
    }
    else {
        x2 = px + length * cos(angle * PI / 180.0);
        y2 = py - length * sin(angle * PI / 180.0);
    }

    // Draw flipper as a red line
    double r = 1.0, g = 0.0, b = 0.0; // Red color
    double flipper_x[2] = { x1, x2 };
    double flipper_y[2] = { y1, y2 };

    line(flipper_x, flipper_y, 2, r, g, b);
}