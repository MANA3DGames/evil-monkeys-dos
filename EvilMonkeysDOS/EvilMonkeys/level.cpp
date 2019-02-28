#include "level.h"
#include "character.h"
#include "enemy.h"
using namespace MANA3DGames;

#include <stdlib.h> // you can include it instead of iostream

Level::Level( DrawEngine *de, int w, int h )
{
	drawArea = de;

	width = w;
	height = h;

	player = 0;

	// Create memory for our level
	level = new char *[width];

	for ( int x = 0; x < width; x++ )
		level[x] = new char[height];

	// Create the level
	createLevel();

	drawArea->setMap( level );
}

Level::~Level()
{
	for ( int x = 0; x < width; x++ )
		delete [] level[x];		// delete each column

	delete [] level;

	for ( Iter = npc.begin(); Iter != npc.end(); Iter++ )
		delete ( *Iter );
}

void Level::createLevel( void )
{
	for ( int x= 0; x < width; x++ )
	{
		for ( int y = 0; y < height; y++ )
		{
			int random = rand() % 100; // % 100 -> this will give us a value between 0 - 99

			if ( y == 0 || y == height - 1 || x == 0 || x == width -1 ) // border of the level
			{
				level[x][y] = TILE_WALL;
			}
			else
			{
				if ( random < 90 || ( x < 3 && y < 3 ) )
					level[x][y] = TILE_EMPTY;
				else
					level[x][y] = TILE_WALL;
			}
		}
	}
}

void Level::draw( void )
{
	// we need to draw the level
	drawArea->drawBackground();
}

void Level::addPlayer( Character *p )
{
	player = p;
}

bool Level::keyPress( char c )
{
	if ( player )
		if ( player->keyPress( c ) )
			return true;
		
	return false;
}

/*
void Level::update( void )
{
	// here is where we'll be able to deal with fireballs moving
	for ( Iter = npc.begin(); Iter != npc.end(); Iter++ )
	{
		( *Iter )->idleUpdate();

		if ( ( *Iter )->isAlive() == false )
		{
			Sprite *temp = *Iter;

			Iter--;

			delete temp;
			 
			npc.remove( temp );
		}
	}
}
*/

void Level::update()
{
   for(Iter = npc.begin(); Iter != npc.end();)
   {
      ( *Iter )->idleUpdate();

      if((*Iter)->isAlive() == false)
      {
         Sprite *temp = *Iter;

         delete temp;
         Iter = npc.erase(Iter);
      }
      else
         Iter++;
   }
}


void Level::addEnemies( int num )
{
	int i = num;

	while ( i > 0 )
	{
		int xpos = int(( float( rand() % 100 ) / 100 ) * ( width - 2 ) + 1);
		int ypos = int(( float( rand() % 100 ) / 100 ) * ( height - 2 ) + 1);

		if ( level[xpos][ypos] != TILE_WALL )
		{
			Enemy *temp = new Enemy( this, drawArea, SPRITE_ENEMY, (float)xpos, float(ypos) );

			temp->addGoal( player );

			addNPC( ( Sprite * )temp );

			i--;
		}
	}
}

void Level::addNPC( Sprite *spr )
{
	npc.push_back( spr );
}