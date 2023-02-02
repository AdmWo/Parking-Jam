#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "MainWindow.h"

#define SECRET_NUMBER 20010901

class Board
{
	public:

		int GetCursorPositionOnBoard( int cursorX, int cursorY) ;
		
		// dane pol na planszy
		
		static const int FrameLength = 128;
		static const int BetweenFrameMarginLength = 2;
		static const int BoardStartX = Graphics::FrameWidth;
		static const int BoardStartY = Graphics::FrameWidth;
		static const int FrameCountX = (Graphics::ScreenWidth-2*Graphics::FrameWidth) / (FrameLength + BetweenFrameMarginLength)+1;
		static const int FrameCountY = (Graphics::ScreenHeight-2*Graphics::FrameWidth) / (FrameLength + BetweenFrameMarginLength)+1;
		bool IsCursorOnBoard(int cursorX, int cursorY);

		int MoveCalc( int*** lvl, int startX, int startY, int dir, int prog=0 ); //dir: 1-N, 2-S, 3-E, 4-W
		int DirectionMove( int startX, int startY, int endX, int endY );
		void Move( int*** lvl, int startX, int startY,int goalX, int goalY, int dir, bool iflen=false, int len=0 );

		void helpDir( int dir, int x1,int& x2,int y1,int& y2, int dt );

		int isRedOn( int*** lvl );
	private:

		
		// dane planszy

		static const int BoardEndX = BoardStartX + (FrameCountX) * FrameLength + BetweenFrameMarginLength * (FrameCountX + 1);
		static const int BoardEndY = BoardStartY + (FrameCountY) * FrameLength + BetweenFrameMarginLength * (FrameCountY + 1);


	public:


		int* mapLevels[7] = {
			mapLevelEmpty,
			mapLevel1,
			mapLevel2,
			mapLevel3,
			mapLevel4,
			mapLevel5,
			mapLevelEmpty
		};

	private: 
		//poziomy
		//-2 - otwarta krawedz
		//-1 - zamknieta krawedz
		//0 - puste miejsce
		//1 - bariera
		//1< - rozne kolory autek x)
		//99 - player

		int mapLevel4[1000] =
		{
			-1, -1, -1, -1, -1, -1, -2, -1, -1, 
			-1, 0, 0, 0, 5, 5, 5, 3, -1, 
			-1, 6, 6, 6, 10, 1, 2, 2, -1, 
			-1, 8, 8, 8, 10, 1, 1, 99, -1, 
			-1, 3, 0, 0, 0, 0, 4, 0, -1, 
			-1, 3, 9, 0, 1, 0, 4, 1, -1, 
			-1, 3, 9, 0, 7, 7, 7, 7, -1, 
			-1, -2, -1, -1, -1, -1, -1, -1, -1 
		};
		int mapLevel2[1000] =
		{
			-1, -1, -1, -1, -1, -1, -1, -1, -1, 
			-1, 99, 0, 0, 2, 4, 0, 0, -1, 
			-1, 1, 1, 1, 2, 4, 1, 0, -1, 
			-2, 6, 0, 1, 2, 0, 5, 5, -1, 
			-1, 6, 0, 1, 3, 3, 3, 0, -1, 
			-1, 6, 0, 1, 1, 1, 1, 0, -1, 
			-1, 0, 0, 0, 0, 0, 0, 0, -1, 
			-1, -1, -1, -1, -1, -1, -1, -1, -1, 
		};
		int mapLevel3[1000] =
		{
			-1, -1, -1, -1, -1, -1, -1, -1, -1, 
			-1, 1, 1, 0, 0, 0, 1, 1, -1, 
			-1, 0, 0, 0, 1, 1, 0, 0, -1, 
			-1, 5, 5, 4, 4, 6, 5, 3, -1, 
			-1, 0, 0, 3, 10, 10, 9, 3, -1, 
			-1, 1, 1, 3, 7, 8, 9, 3, -1, 
			-1, 99, 99, 3, 7, 8, 9, 0, -2, 
			-1, -1, -1, -1, -1, -1, -1, -1, -1, 
		};
		int mapLevel5[1000] =
		{
			-1, -1, -1, -1, -1, -1, -1, -1, -1, 
			-1, 2, 2, 0, 0, 0, 3, 1, -1, 
			-1, 0, 0, 1, 0, 0, 3, 8, -1, 
			-1, 4, 6, 0, 1, 1, 9, 0, -1, 
			-1, 4, 3, 7, 0, 1, 0, 0, -2, 
			-1, 4, 3, 5, 5, 0, 1, 1, -1, 
			-1, 4, 3, 2, 2, 2, 2, 99, -1, 
			-1, -1, -1, -1, -1, -1, -1, -1, -1, 
		};
		int mapLevel1[1000] =
		{
			-1, -1, -1, -1, -1, -1, -1, -1, -1, 
			-1, 2, 2, 2, 2, 2, 2, 2, -1, 
			-1, 9, 9, 9, 0, 8, 8, 8, -1, 
			-1, 0, 0, 0, 0, 5, 5, 5, -1, 
			-1, 0, 0, 0, 0, 0, 10, 0, -1, 
			-1, 99, 0, 0,0, 0, 10, 0, -2, 
			-1, 5, 5, 7, 7, 5, 5, 5, -1, 
			-1, -1, -1, -1, -1, -1, -1, -1, -1, 
		};
		int mapLevelEmpty[1000] =
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 
			0, 0, 0, 0, 0, 0, 0, 0, 0, 
			0, 0, 0, 0, 0, 0, 0, 0, 0, 
			0, 0, 0, 0, 0, 0, 0, 0, 0, 
			0, 0, 0, 0, 0, 0, 0, 0, 0, 
			0, 0, 0, 0, 0, 0, 0, 0, 0, 
			0, 0, 0, 0, 0, 0, 0, 0, 0, 
			0, 0, 0, 0, 0, 0, 0, 0, 0 
		};

};