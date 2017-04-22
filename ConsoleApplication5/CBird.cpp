#include "CBird.h"

int CBird::getAngle(double speed)
{
	if (speed == 0)
		return 0;
	if (speed < 0)
	{
		speed *= -1;
		if (speed > jump_add / 2)
			return 2;
		else
			return 1;
	}
	else
	{
		int a[43] = { 1,1,1,1,1,1,3,3,3,3,4,4,4,4,5,5,5,6,6,7,7,8,8,8,9,9,9,10,10,11,11 ,11,11,11,11};
		int ret = a[(int)speed];
		if (ret > 11)return 11;
		return ret;
		//0~32f
		//3 ~ 11
	}
}

int CBird::getY()
{
	return m_y;
}


void CBird::initbird(int style)
{
	m_bird_style[style] = imread(MPATH + bird_style_filename[style]);
	m_bird_style_[style] = imread(MPATH + bird_style_filename[style], 0);
	m_bird[style][0] = m_bird_style[style];
	m_bird_[style][0] = m_bird_style_[style];
	Point2f center;  // 旋转中心 
	Mat rotateMat;
	Mat rotateImg;
	for (int i = 1; i <= 2; i++)
	{
		int angle = i * 10 + 5;
		m_bird[style][i] = m_bird_style[style];
		m_bird_[style][i] = m_bird_style_[style];
		center = cv::Point2f(m_bird[style][i].cols / 2, m_bird[style][i].rows / 2);		// 旋转中心 
		rotateMat = cv::getRotationMatrix2D(center, angle, 1);
		warpAffine(m_bird[style][i], rotateImg, rotateMat, m_bird[style][i].size());
		m_bird[style][i] = rotateImg;

		center = cv::Point2f(m_bird_[style][i].cols / 2, m_bird_[style][i].rows / 2);		// 旋转中心 
		rotateMat = cv::getRotationMatrix2D(center, angle, 1);
		warpAffine(m_bird_[style][i], rotateImg, rotateMat, m_bird_[style][i].size());
		m_bird_[style][i] = rotateImg;
	}
	for (int i = 3; i <= 11; i++)
	{
		int angle = -(i - 2) * 10;
		m_bird[style][i] = m_bird_style[style];
		m_bird_[style][i] = m_bird_style_[style];
		center = cv::Point2f(m_bird[style][i].cols / 2, m_bird[style][i].rows / 2);		// 旋转中心 
		rotateMat = cv::getRotationMatrix2D(center, angle, 1);
		warpAffine(m_bird[style][i], rotateImg, rotateMat, m_bird[style][i].size());
		m_bird[style][i] = rotateImg;

		center = cv::Point2f(m_bird_[style][i].cols / 2, m_bird_[style][i].rows / 2);		// 旋转中心 
		rotateMat = cv::getRotationMatrix2D(center, angle, 1);
		warpAffine(m_bird_[style][i], rotateImg, rotateMat, m_bird_[style][i].size());
		m_bird_[style][i] = rotateImg;
	}
}

CBird::CBird(Mat bg)
{
	m_bg = bg;
	m_y = defaultY;

	//初始化小鸟素材
	for (int i = 0; i < 3; i++)
	{
		initbird(i);
	}
	imageROI = m_bg(Rect(80, m_y, m_bird_style[0].cols, m_bird_style[0].rows));



	m_bird_istyle = 0;
	m_cur_speed = -jump_add;
	time_ = 0;
}

CBird::~CBird()
{
}

void CBird::draw()
{
	time_++;
	if (m_y >= 400)
	{
		m_y = defaultY, m_cur_speed = -jump_add;
	}

	if (m_bird_istyle >= 30)m_bird_istyle = 0;
	if (time_ >= 3) //处理位移的频率
	{
		m_cur_speed += G;
		m_y += (int)m_cur_speed;
		time_ = 0;
	}
	//获得区域
	imageROI = m_bg(Rect(80, m_y, m_bird_style[0].cols, m_bird_style[0].rows));

	//处理 旋转

	//输出
	//m_bird_style[m_bird_istyle / 10].copyTo(imageROI, m_bird_style_[m_bird_istyle / 10]);
	//rotateImg.copyTo(imageROI, rotateImg);
	m_bird[m_bird_istyle / 10][getAngle(m_cur_speed)].copyTo(imageROI, m_bird_[m_bird_istyle / 10][getAngle(m_cur_speed)]);
	//改变样式
	m_bird_istyle += 3;
}

void CBird::jump()
{
	m_cur_speed = -jump_add;
	draw();
	//imageROI = m_bg(Rect(80, m_y, m_bird_style[0].cols, m_bird_style[0].rows));
}

int CBird::getWidth()
{
	return m_bird_style[0].cols;
}

int CBird::getHeight()
{
	return m_bird_style[0].rows;
}
