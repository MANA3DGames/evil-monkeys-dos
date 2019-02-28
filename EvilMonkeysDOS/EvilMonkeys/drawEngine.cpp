#include "drawEngine.h"

#include <Windows.h>
#include <iostream>

using namespace std;
using namespace MANA3DGames;

DrawEngine::DrawEngine( int xSize, int ySize )
{
	screenWidth = xSize;
	screenHeight = ySize;

	// set cursor visibility to false
	cursorVisibility( false );

	map = 0;
}

DrawEngine::~DrawEngine()
{
	// set cursor visibility to true
	cursorVisibility( true );

	gotoxy( 0, screenHeight );
}

int DrawEngine::createSprite( int index, char c )
{
	if ( index >= 0 && index < 16 )
	{
		spriteImage[index] = c;
		return index;
	}

	return -1;
}

void DrawEngine::deleteSprite( int index )
{
	// in this implementaion we don't need it
}

void DrawEngine::drawSprite( int index, int posx, int posy )
{
	// go to the correct location
	gotoxy( posx, posy );

	// draw the image
	cout << spriteImage[index];
}

void DrawEngine::eraseSprite( int posx, int posy )
{
	gotoxy( posx, posy );
	cout << ' ';
}

void DrawEngine::setMap( char **data )
{
	map = data;
}

void DrawEngine::createBackgroundTile( int index, char c )
{
	if ( index >= 0 && index < 16 )
	{
		tileImage[index] = c;
	}
}

void DrawEngine::drawBackground( void )
{
	if ( map )
	{
		for ( int y = 0; y < screenHeight; y++ )
		{
			gotoxy( 0, y ); // to make sure we are at the right pos

			for ( int x = 0; x < screenWidth; x++ )
				cout << tileImage[map[x][y]];
		}
	}
}

void DrawEngine::gotoxy( int x, int y )
{
	HANDLE output_handle;	// a handle is a unique idea that associated with something inside the system
	COORD pos;

	pos.X = x;
	pos.Y = y;

	output_handle = GetStdHandle( STD_OUTPUT_HANDLE );

	SetConsoleCursorPosition( output_handle, pos );
}

void DrawEngine::cursorVisibility( bool visibility )
{
	HANDLE output_handle;
	output_handle = GetStdHandle( STD_OUTPUT_HANDLE );

	CONSOLE_CURSOR_INFO cciInfo;
	cciInfo.dwSize = 1;
	cciInfo.bVisible = visibility;

	SetConsoleCursorInfo( output_handle, &cciInfo );
}

