void draw_background();
void draw_stage();

class triangleStage {

public:
	int vx1, vx2, vx3; // x coord of vertices for triangular stage elements
	int vy1, vy2, vy3; // y coord of vertices for triangular stage elements
	//static int triangleID;

	triangleStage(int x1, int y1, int x2, int y2, int x3, int y3);
};

//int triangleStage::triangleID = 0; // ID of triangle stage element, may be useful

class circleStage {

public:
	int cx, cy; // center of circular stage element
	int n; // number of points in circle
	int rad; // radius of circlular stage element
	//static int circleID;

	circleStage::circleStage(int center_x, int center_y, int number_points, int radius); // center x, y, number points, radius
};

//int circleStage::circleID=0; // ID of circle stage element, may be useful
