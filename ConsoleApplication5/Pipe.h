#include "cv.h"
#include "highgui.h"
#include<stdlib.h>
#pragma once
using namespace cv;
class Pipe
{
private:
	int m_speed;
	int m_x;
	int m_height;
	int diff;
	int pipe_width;
	
	Mat mpipe;
	Mat mpipe_mask; 
	Mat Cmpipe;
	Mat Cmpipe_mask;

	Mat mpipe_;
	Mat mpipe_mask_;
	Mat Cmpipe_;
	Mat Cmpipe_mask_;

	Mat m_mat_bg;
public:
	const std::string  MPATH = "C:\\Users\\wax\\Desktop\\flappybird\\";
	Pipe(Mat bg,int speed,int height);
	bool pipe_draw();
	int getX();
	int getHeight();
	int getWidth();
	int getDif();
	~Pipe();
};

