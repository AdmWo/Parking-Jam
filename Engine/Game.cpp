/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"


int xStart,xEnd,yStart,yEnd;
int temp,kotek,tempClick,MousePos,tempDir;
int sx,sy,goalX,goalY,tx,ty;

int nextLevel = 1;
int currLevel = 0;

int*** board = NULL;



/*--------------------TO DO
* BUG jak sie kwadrat robi w inny kwadrat zaraz obok //DONE
* autka o wiekszych wymiarach //DONE
* zeby pomaranczowych kwadratow sie nie dalo ruszac  //DONE
* jak sie wysle w otwarte to zeby wszystko znikalo //DONE
* animacje ? //ehhh
* crash przy rysowaniu kolek //DONE
* jak sie jest zaraz obok bramy to nie znika  //DONE
* jak sie zestaw strzeli w brame to znika tylko pierwszy //DONE
* zeby autka jechaly w dobrych kierunkach  //DONE
* zeby tylko czerwone autko moglo wyjechac //DONE
* gameplay(levele)? //DONE
* inne autka nie zatrzymuja sie przed bramka
*/

void free_data(int ***data, size_t xlen, size_t ylen)
{
	size_t i, j;

	for (i=0; i < xlen; ++i) {
		if (data[i] != NULL) {
			for (j=0; j < ylen; ++j)
				free(data[i][j]);
			free(data[i]);
		}
	}
	free(data);
}

int ***alloc_data(size_t xlen, size_t ylen)
{
	int ***p;
	size_t i, j;

	if( (p = (int***)malloc( xlen * sizeof *p ) ) == NULL) 
	{
		perror("malloc 1");
		return NULL;
	}

	for (i=0; i < xlen; ++i)
		p[i] = NULL;

	for (i=0; i < xlen; ++i)
		if ((p[i] = (int**)malloc(ylen * sizeof *p[i])) == NULL) {
			perror("malloc 2");
			free_data(p, xlen, ylen);
			return NULL;
		}

	for (i=0; i < xlen; ++i)
		for (j=0; j < ylen; ++j)
			p[i][j] = NULL;

	for (i=0; i < xlen; ++i)
		for (j=0; j < ylen; ++j)
			if ((p[i][j] = (int*)malloc( 5 * sizeof *p[i][j])) == NULL) {
				perror("malloc 3");
				free_data(p, xlen, ylen);
				return NULL;
			}

	return p;
}

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	drw( gfx )
{
}


void Game::Pre()
{
	
	board = alloc_data(Board::FrameCountX+2, Board::FrameCountY+2);
	
	int count=0;

	for( int j = 0; j < Board::FrameCountY+2; j++)
		for( int i = 0; i < Board::FrameCountX+2; i++ )
		{
			board[i][j][1] = count++;
		}

}

void Game::LoadLevel()
{
	for( int j = 0; j < Board::FrameCountY+2; j++)
		for( int i = 0; i < Board::FrameCountX+2; i++ )
		{
			board[i][j][2] = brd.mapLevels[currLevel][j*(Board::FrameCountX+2)+i];
		}
}

void Game::Go()
{
	gfx.BeginFrame();	

	if( nextLevel )
	{
		currLevel++;
		LoadLevel();
		nextLevel = 0;
	}
	
	
	ComposeFrame();
	UpdateModel();

	if( currLevel == 6 )
	{
		DisplayResourceNAMessageBox();
	}

	gfx.EndFrame();
}

void Game::UpdateModel()
{

	if( wnd.mouse.LeftIsPressed() && !tempClick )
	{
		xStart = wnd.mouse.GetPosX();
		yStart = wnd.mouse.GetPosY();
	}

	

	if( tempClick  && brd.IsCursorOnBoard( wnd.mouse.GetPosX(),wnd.mouse.GetPosY() )  ) 
	{
		xEnd = wnd.mouse.GetPosX();
		yEnd = wnd.mouse.GetPosY();

		if(	brd.GetCursorPositionOnBoard( wnd.mouse.GetPosX(),wnd.mouse.GetPosY() ) > -1 )
			MousePos = brd.GetCursorPositionOnBoard( wnd.mouse.GetPosX(),wnd.mouse.GetPosY());
		
		drw.DrawCircle( xStart, yStart, 14, Colors::Gray );  //nie rysowac kolek o r = ramce bo crashuje jak sie da blisko xd
		drw.DrawLine( xStart, yStart, xEnd, yEnd, Colors::Yellow );
		drw.DrawCircle( xEnd, yEnd, 14, Colors::Gray );

	}

		if( !wnd.mouse.LeftIsPressed() && tempClick )
		{
			
			tempDir = brd.DirectionMove(xStart,yStart,xEnd,yEnd);

			if( tempDir )
			{
				temp = brd.GetCursorPositionOnBoard( xStart,yStart );

				sx = temp%(Board::FrameCountX+2);
				sy = temp/(Board::FrameCountX+2);
				if( board[sx][sy][2] > 1 )
				{
					brd.helpDir( 4-((tempDir-1)/2)*2,sx,tx,sy,ty,1 );
					if( board[sx][sy][2] != board[tx][ty][2] ) 
					{
						brd.helpDir( 3-((tempDir-1)/2)*2,sx,tx,sy,ty,1 );
						if( board[sx][sy][2] != board[tx][ty][2] )
						{
							brd.Move(board,sx,sy,goalX,goalY,tempDir);

							if( !brd.isRedOn( board ) )
								nextLevel = 1;
						}
					}
				}
			}

			}

	if( wnd.mouse.IsInWindow() )
		tempClick = wnd.mouse.LeftIsPressed();
}

void Game::ComposeFrame()
{	
	drw.DrawLevel( board, Colors::Brown, Colors::Blue,Colors::Yellow2,Colors::Pink, Colors::Green, Colors::Magenta,
		Colors::Cyan,Colors::Lime, Colors::Wojtek, Colors::Orange, Colors::Red, Colors::DarkGray );

	drw.DrawNet( Colors::DarkGray2 );
}

int Game::DisplayResourceNAMessageBox()
{
	int msgboxID = MessageBox(
		wnd.hWnd,
		(LPCWSTR)L"Brawo, wygrales",
		(LPCWSTR)L"gz",
		MB_ICONQUESTION | MB_RETRYCANCEL | MB_SETFOREGROUND 
	);

	switch (msgboxID)
	{
		
	case IDRETRY:
		currLevel = 0;
		nextLevel = 1;
		break;
	case IDCANCEL:
		board = 0;
		free_data(board,Board::FrameCountX+2, Board::FrameCountY+2);
		wnd.Kill();
		break;
	}

	return msgboxID;
}