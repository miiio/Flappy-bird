#include "cv.h"
#include "highgui.h"  
#include "CBird.h"
#include "Pipe.h"
#include<vector>
#pragma once
using namespace cv;
class Scenes
{
private:
	IplImage* m_lpl_bg;

	Mat m_mat_land;
	Mat m_mat_land_;

	Mat m_mat_clear;
	Mat m_mat_clear_mask;
	Mat m_mat_bg;

	Mat m_imageROI_clear;
	Mat m_imageROI_land;
	Mat m_imageROI_score;
	Mat m_mat_number[10];
	Mat m_mat_number_mask[10];

	int land_speed;
	int land_pos;
	int bird_style;
	int score;

	CBird* m_bird;

	std::vector<Pipe*> pipe_v;
public:
	const std::string  MPATH = "C:\\Users\\wax\\Desktop\\flappybird\\";
    const string bird_style_filename[3] = { "bird2_0.png","bird2_1.png","bird2_2.png" };
	void scenes_clear();
	void land_roll();
	void brid_draw();
	void scenes_draw();
	void pipe_make();
	void jump();
	void score_show();
	bool collision_check();
	Scenes();
	~Scenes();
};

