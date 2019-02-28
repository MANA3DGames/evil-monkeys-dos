#ifndef GAME_H
#define GAME_H

#include "drawEngine.h"
#include "level.h"
#include "character.h"
#include "mage.h"

namespace MANA3DGames
{
	class Game
	{
	public:
		bool run(void);

	protected:
		bool getInput(char *c);
		void timerUpdate(void);

	private:
		Level *level;
		Mage *player;

		double frameCount;
		double startTime;
		double lastTime;

		int posx;

		DrawEngine drawArea;
	};
}
#endif