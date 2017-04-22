#include "Pipe.h"

Pipe::Pipe(Mat bg, int speed, int height)
{
	m_height = height;
	diff = 90;
	m_speed = speed;
	m_x = bg.cols;
	Cmpipe = imread(MPATH + "pipe_down.png");
	pipe_width = Cmpipe.cols;
	Cmpipe_mask = imread(MPATH + "pipe_down.png", 0);

	Cmpipe_ = imread(MPATH + "pipe_up.png");
	Cmpipe_mask_ = imread(MPATH + "pipe_up.png", 0);

	m_mat_bg = bg;
}

bool Pipe::pipe_draw()
{
	m_x -= m_speed;
	if (m_x >= -Cmpipe.cols)
	{
		if (m_x >= m_mat_bg.cols - pipe_width)
		{
			Rect rect(0, Cmpipe.rows - m_height, m_mat_bg.cols - m_x, m_height);
			mpipe = Cmpipe(rect);
			mpipe_mask = Cmpipe_mask(rect);

			Rect rect_(0, 0, m_mat_bg.cols - m_x, 400 - m_height - diff);
			mpipe_ = Cmpipe_(rect_);
			mpipe_mask_ = Cmpipe_mask_(rect_);
		}
		if (m_x < 0)
		{
			//m_speed /= 2;
			mpipe = Cmpipe;
			mpipe_mask = Cmpipe_mask;
			Rect rect(-m_x, Cmpipe.rows - m_height, Cmpipe.cols + m_x, m_height);
			mpipe = Cmpipe(rect);
			mpipe_mask = Cmpipe_mask(rect);

			mpipe_ = Cmpipe_;
			mpipe_mask_ = Cmpipe_mask_;
			Rect rect_(-m_x, 0, Cmpipe.cols + m_x, 400 - m_height - diff);
			mpipe_ = Cmpipe_(rect_);
			mpipe_mask_ = Cmpipe_mask_(rect_);
		}

		Mat imageROI;
		imageROI = m_mat_bg(Rect(m_x <= 0 ? 0 : m_x - 1, 0, mpipe.cols, mpipe.rows));
		mpipe.copyTo(imageROI, mpipe_mask);

		Mat imageROI_;
		imageROI_ = m_mat_bg(Rect(m_x <= 0 ? 0 : m_x - 1, m_height + diff, mpipe_.cols, mpipe_.rows));
		mpipe_.copyTo(imageROI_, mpipe_mask_);
		return true;
	}
	else
	{
		return false;
	}
}

int Pipe::getX()
{
	return m_x;
}

int Pipe::getHeight()
{
	return m_height;
}

int Pipe::getWidth()
{
	return Cmpipe.cols;
}

int Pipe::getDif()
{
	return diff;
}


Pipe::~Pipe()
{
}
