#include "Scenes.h"
#define RANDHEIGHT ((rand() % (200+ 1)) + 50)
#define YINMID  ( birdY>pHeight && birdY+ birdHeight<pHeight+pDiff)
#define XINMID (!(  birdWidth+80 <x ||  x+pWidth<80 ))

void Scenes::scenes_clear()
{
	m_mat_clear.copyTo(m_imageROI_clear);
}
void Scenes::land_roll()
{
	land_pos += land_speed;
	if (land_pos >= m_mat_land.cols)
		land_pos = 0;
	for (int i = 0; i < m_mat_land.rows; i++)
	{
		uchar * data = m_mat_land_.ptr<uchar>(i); //µÚiÐÐ
		for (int j = 0; j < m_mat_land.cols; j++)
		{
			int jj = (j + land_pos) % m_mat_land.cols;
			m_mat_bg.ptr<uchar>(i + 400)[j * 3] = data[jj * 3];
			m_mat_bg.ptr<uchar>(i + 400)[j * 3 + 1] = data[jj * 3 + 1];
			m_mat_bg.ptr<uchar>(i + 400)[j * 3 + 2] = data[jj * 3 + 2];
		}
	}
}

void Scenes::brid_draw()
{
	scenes_clear();
	m_bird->draw();
}

void Scenes::scenes_draw()
{
	imshow("flappy bird", m_mat_bg);
	//cvShowImage("flappy bird", m_lpl_bg);
}

void Scenes::pipe_make()
{
	bool flag = false, flag2 = false;
	for (int i = 0; i < pipe_v.size(); i++)
	{
		if (!pipe_v[i]->pipe_draw())
			flag2 = true;
		//if (pipe_v[i]->getX() == m_mat_bg.cols / 2)
		if (pipe_v[i]->getX() == m_mat_bg.cols - 180)
			flag = true;
	}

	if (flag)
	{
		pipe_v.push_back(new Pipe(m_mat_bg, land_speed, RANDHEIGHT));
	}
	if (flag2)
	{
		free(pipe_v[0]);
		pipe_v.erase(pipe_v.begin());
	}
}

void Scenes::jump()
{
	m_bird->jump();
}

void Scenes::score_show()
{
	m_mat_number[score].copyTo(m_imageROI_score, m_mat_number_mask[score]);
}

bool Scenes::collision_check()
{
	int birdY = m_bird->getY();
	for (int i = 0; i < pipe_v.size(); i++)
	{
		Pipe* p = pipe_v.at(i);
		int x = p->getX();
		int birdWidth = m_bird->getWidth() - 15;
		int birdHeight = m_bird->getHeight() - 10;
		int pWidth = p->getWidth();
		int pHeight = p->getHeight() - 10;
		int pDiff = p->getDif() + 10;
		if (XINMID && !YINMID)
		{
			return true;
		}
		else if (x + pWidth == 80 - 2)
		{
			score++;
			printf("Score:%d\n", score);
		}
	}

	return false;
}
Scenes::Scenes()
{
	cvNamedWindow("flappy bird");

	m_lpl_bg = cvLoadImage((MPATH + "bg_day.png").c_str());
	m_mat_bg = Mat(m_lpl_bg); //background!

	m_mat_clear = imread(MPATH + "clear.png");
	m_mat_clear_mask = imread(MPATH + "clear.png", 0);
	m_imageROI_clear = m_mat_bg(Rect(0, 0, m_mat_clear.cols, m_mat_clear.rows));
	m_imageROI_land = m_mat_bg(Rect(0, 400, m_mat_bg.cols, m_mat_bg.rows - 400));

	m_mat_land = imread(MPATH + "land.png");
	m_mat_land_ = imread(MPATH + "land.png");
	string tmps[10] = { "font_048.png","font_049.png","font_050.png","font_051.png","font_052.png","font_053.png","font_054.png", "font_055.png",
						"font_056.png", "font_057.png" };
	for (int i = 0; i < 10; i++)
	{
		m_mat_number[i] = imread(MPATH + tmps[i]);
		m_mat_number_mask[i] = imread(MPATH + tmps[i], 0);
	}
	m_imageROI_score = m_mat_bg(Rect(m_mat_bg.cols / 2, 50, m_mat_number[0].cols, m_mat_number[0].rows));
	land_pos = 0;
	land_speed = 2;
	bird_style = 0;
	score = 2;

	srand((unsigned)time(NULL));
	m_bird = new CBird(m_mat_bg);
	pipe_v.push_back(new Pipe(m_mat_bg, land_speed, RANDHEIGHT));
}


Scenes::~Scenes()
{

}
