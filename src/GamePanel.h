#ifndef __GAMEPANEL_H_
#define __GAMEPANEL_H_

#include "Map.h"

#include "Panel.h"

#include "Rect.h"


class GamePanel : public Panel
{
	public:
		GamePanel(Window*, Camera*);
		~GamePanel();
		void render();
		void update();
		void setActive();
		void keyOnePress();
		void keyTwoPress();
		void keyThreePress();
		Shader2t * shader;
		Map * map;
		ColRect * health;
		TexRect * selected, * death, * boneSign, * waves;
		MultiRect * keyOne, * keyTwo, * keyThree, * digitOne, * digitTwo, * digitThree, * waveCount;
		int wave;
};

#endif
