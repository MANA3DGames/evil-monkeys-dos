#include "game.h"
#include "drawEngine.h" // in the header also!!! I wonder WHY!!!

#include <conio.h>
#include <iostream>
#include <windows.h>

using namespace std;
using namespace MANA3DGames;

// This is going to give us ~ 30 fps
#define GAME_SPEED 33.33


bool Game::run(void)
{
	level = new Level( &drawArea, 30, 20 );

	// Search -> "ascii character codes"
	drawArea.createBackgroundTile( TILE_EMPTY, ' ' );
	drawArea.createBackgroundTile( TILE_WALL, 219 );

	drawArea.createSprite( SPRITE_PLAYER, 1 );
	drawArea.createSprite( SPRITE_ENEMY, '$' );
	drawArea.createSprite( SPRITE_FIREBALL, '*' );

	player = new Mage( level, &drawArea, 0 );

	level->draw();
	level->addPlayer( player );
	level->addEnemies( 3 );

	char key = ' ';

	startTime = timeGetTime();
	frameCount = 0;
	lastTime = 0;

	posx = 0;

	player->move( 0, 0 );

	while ( key != 'q' )
	{
		while ( !getInput( &key ) )
		{
			timerUpdate();
		}

		level->keyPress( key );

		//cout << "Pressed key : " << key << endl;
	}

	delete player;

	//cout << frameCount / ( ( timeGetTime() - startTime ) / 1000 ) << "FPS" << endl;
	//cout << "End of the Game!" << endl;
	
	cin >> frameCount;

	return true;
}

bool Game::getInput( char *c )
{
	if ( kbhit() )
	{
		*c = getch(); // get the character thats been hit 

		return true;
	}

	return false;
}

void Game::timerUpdate( void )
{
	// to limit the fps
	double currentTime = timeGetTime() - lastTime;

	// 1000/30 = 33.3333
	if ( currentTime < GAME_SPEED )
		return;

	// Here, we are in the right time frame
	
	level->update();

	// *************************

	frameCount++;

	lastTime = timeGetTime();
}