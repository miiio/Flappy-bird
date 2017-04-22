#include "Scenes.h"
using namespace cv;
int main()
{
	while (1)
	{
		Scenes* scenes = new Scenes();
		cvWaitKey(0);
		while (1)
		{
			if (scenes->collision_check())
				break;
			scenes->brid_draw();
			scenes->land_roll();
			scenes->pipe_make();
			scenes->score_show();
			scenes->scenes_draw();
			if (cvWaitKey(5) != -1)
				scenes->jump();
		}
		cvWaitKey(0);
	}
	return 0;
}