#ifndef LEVEL_H
#define LEVEL_H

#include "drawEngine.h"

#include<list>
using std::list;

namespace MANA3DGames
{
	//#include "character.h" // we can us -> class Character; to avoid Circular Referencing.
	class Sprite;
	class Character;	// This is a pre-definition, instead of using #include "character.h" because this will cause us a problem, (this mean Character is defined some where so the compiler believe us)


	enum
	{
		SPRITE_PLAYER,
		SPRITE_ENEMY,
		SPRITE_FIREBALL
	};

	enum
	{
		TILE_EMPTY,
		TILE_WALL
	};

	class Level
	{
	public:
		Level(DrawEngine *de, int width = 30, int height = 20);
		~Level();

		void addPlayer(Character *p);
		void update(void);
		void draw(void);
		bool keyPress(char c);

		void addEnemies(int num);
		void addNPC(Sprite *spr);

		friend class Sprite;	// which means it will have access on public & protected data

	protected:
		void createLevel(void);

	private:
		int width;
		int height;

		char **level;

		Character *player;

		DrawEngine *drawArea;

	public:
		list <Sprite *> npc;
		list <Sprite *>::iterator Iter;
	};
}
#endif