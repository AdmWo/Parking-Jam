#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "MainWindow.h"
#include "Board.h"

class Drawin
{
public:

	
	Drawin( class Graphics& key );
	
	Drawin( const Drawin& ) = delete;
	Drawin& operator=( const Drawin& ) = delete;

	void DrawLine( int x0, int y0, int x1, int y1, Color c );
	void DrawCircle( int x0, int y0, int r, Color c );

	void DrawSquare( int cord, Color c );

	void DrawLevel( int*** lvl, Color c1, Color c2, Color c3, Color c4, Color c5, Color c6, Color c7, Color c8, Color c9, Color b, Color red, Color bg );

	void DrawNet( Color c );


private:

	


	Graphics& gfx2;

	
	
};
