#pragma once

class Flipper {
public:
    double px, py;         // center of rotation
    double length;         // length of the flipper
    double angle;          // current angular position
    double restAngle;      // resting position angle
    double maxAngle;       // maximum angular rotation
    double angularSpeed;   // flipper omega

    Flipper(double pivot_x, double pivot_y, double len, double rest_ang, double max_ang, double ang_speed);

    void update(bool keyPressed, bool counterClockwise);

    void draw(bool pivotAtRight);
};
