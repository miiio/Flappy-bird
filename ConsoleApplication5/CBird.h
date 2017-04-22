#pragma once
#include<cv.h>
#include<highgui.h>
using namespace cv;
class CBird
{
private:
	int m_bird_istyle;

	Mat m_bird_style[3];
	Mat m_bird_style_[3];
	Mat m_bird[3][12];
	Mat m_bird_[3][12];
	Mat m_bg;
	Mat imageROI;
	int m_y;
	double m_cur_speed;
	int time_;

	void initbird(int i);
	int getAngle(double speed);
public:
	const std::string  MPATH = "C:\\Users\\wax\\Desktop\\flappybird\\";
	const std::string bird_style_filename[3] = { "bird2_0.png","bird2_1.png","bird2_2.png" };
	const int defaultY = 180;
	const double G = 2;
	const int jump_add = 14;

	CBird(Mat bg);
	~CBird();
	void draw();
	void jump();
	int getWidth();
	int getHeight();
	int getY();
};

