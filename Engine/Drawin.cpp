#include "Drawin.h"


Drawin::Drawin( Graphics& key )
	:
	gfx2( key )
{
}



void Drawin::DrawLine( int x0, int y0, int x1, int y1, Color c ) //algorytm Bresenhama
{
	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;

	dx = x1 - x0;
	dy = y1 - y0;

	dx1 = abs(dx);
	dy1 = abs(dy);

	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;

	if (dy1 <= dx1) {
		if (dx >= 0) {
			x = x0;
			y = y0;
			xe = x1;
		} else {
			x = x1;
			y = y1;
			xe = x0;
		}
		gfx2.PutPixel(x, y, c);
		for (i = 0; x<xe; i++) {
			x = x + 1;
			if (px<0) {
				px = px + 2 * dy1;
			} else {
				if ((dx<0 && dy<0) || (dx>0 && dy>0)) {
					y = y + 1;
				} else {
					y = y - 1;
				}
				px = px + 2 * (dy1 - dx1);
			}
			gfx2.PutPixel(x, y, c);
		}
	} else {
		if (dy >= 0) {
			x = x0;
			y = y0;
			ye = y1;
		} else {
			x = x1;
			y = y1;
			ye = y0;
		}
		gfx2.PutPixel(x, y, c);
		for (i = 0; y<ye; i++) {
			y = y + 1;
			if (py <= 0) {
				py = py + 2 * dx1;
			} else {
				if ((dx<0 && dy<0) || (dx>0 && dy>0)) {
					x = x + 1;
				} else {
					x = x - 1;
				}
				py = py + 2 * (dx1 - dy1);
			}
			gfx2.PutPixel(x, y, c);
		}
	}
}

void Drawin::DrawCircle(int x0, int y0, int r, Color c) //algorytm Bresenhama
{
	int x = r;
	int y = 0;
	int decision = 4 - 2 * r;

	while (y <= x) {
		gfx2.PutPixel(x + x0, y + y0, c);
		gfx2.PutPixel(y + x0, x + y0, c);
		gfx2.PutPixel(-x + x0, y + y0, c);
		gfx2.PutPixel(-y + x0, x + y0, c);
		gfx2.PutPixel(-x + x0, -y + y0, c);
		gfx2.PutPixel(-y + x0, -x + y0, c);
		gfx2.PutPixel(x + x0, -y + y0, c);
		gfx2.PutPixel(y + x0, -x + y0, c);
		if (decision < 0) {
			decision += 4 * y + 6;
		} else {
			decision += 4 * (y - x) + 10;
			x--;
		}
		y++;
	}
}

void Drawin::DrawSquare( int cord, Color c )
{	
	int tempx,tempy;
	//kordynaty lewego gornego rogu
	tempx = ( cord % (Board::FrameCountX+2) )*( Board::FrameLength + Board::BetweenFrameMarginLength ) 
		- Board::FrameLength - Board::BetweenFrameMarginLength + Board::BoardStartX;
	tempy = ( cord / (Board::FrameCountX+2) )*( Board::FrameLength + Board::BetweenFrameMarginLength ) 
		- Board::FrameLength - Board::BetweenFrameMarginLength + Board::BoardStartY;

	Color tempc = Colors::Orange;

	for( int i = 0; i < Board::FrameLength; i++ )
		for( int j = 0; j < Board::FrameLength; j++ )
		{
			if( tempx + i > 0 && tempx + i < Graphics::ScreenWidth && tempy + j > 0 && tempy + j < Graphics::ScreenHeight )
			{
			gfx2.PutPixel( tempx + i, tempy + j, c );

			if( c.GetR() == tempc.GetR() && c.GetG() == tempc.GetG() && c.GetB() == tempc.GetB() )
			{ 
				if( (j + i)%(Board::FrameLength/4) == Board::FrameLength%(Board::FrameLength/4) ||
					(j + i)%(Board::FrameLength/4) == Board::FrameLength%(Board::FrameLength/4) +1 ||
					(j + i)%(Board::FrameLength/4) == Board::FrameLength%(Board::FrameLength/4) + 2 )

					if( i > Graphics::FrameWidth && i < Board::FrameLength - Graphics::FrameWidth && 
						j > Graphics::FrameWidth && j < Board::FrameLength - Graphics::FrameWidth )
						if( i > 17 || j > 17 ) //nawet nie pytaj
							gfx2.PutPixel( tempx + i, tempy + j, Colors::DarkGray2 );
			}
			
			}
		}

	
}




void Drawin::DrawLevel( int*** lvl, Color c1, Color c2, Color c3, Color c4, Color c5, Color c6, Color c7, Color c8, Color c9, Color b, Color red, Color bg )
{
	for( int i = 0; i < (Board::FrameCountX+2); i++)
		for( int j = 0; j < (Board::FrameCountY+2); j++)
		{
			
				switch( lvl[i][j][2] )
				{
				case -1: DrawSquare( lvl[i][j][1], b); break;
				case 1:  DrawSquare( lvl[i][j][1], b); break;
				case 2: DrawSquare( lvl[i][j][1], c2); break;
				case 3: DrawSquare( lvl[i][j][1], c3); break;
				case 4: DrawSquare( lvl[i][j][1], c4); break;
				case 5: DrawSquare( lvl[i][j][1], c5); break;
				case 6: DrawSquare( lvl[i][j][1], c6); break;
				case 7: DrawSquare( lvl[i][j][1], c7); break;
				case 8: DrawSquare( lvl[i][j][1], c8); break;
				case 9: DrawSquare( lvl[i][j][1], c9); break;
				case 99: DrawSquare( lvl[i][j][1], red); break;
				case 0: DrawSquare( lvl[i][j][1], bg); break;
				case -2: DrawSquare( lvl[i][j][1], bg); break;
				default:DrawSquare( lvl[i][j][1], c1); break;
				}
		}
}

void Drawin::DrawNet( Color c )
{
	for( int j = 0; j < Graphics::ScreenHeight; j++ )
	{	

		for( int i = 0; i < Graphics::ScreenWidth; i++ )
		{

			for( int frame = 0; frame < Board::BetweenFrameMarginLength; frame ++)
				if( (i - Board::BoardStartX +2 )% (Board::FrameLength + Board::BetweenFrameMarginLength) == frame ) 
					gfx2.PutPixel( i, j, c );

			for( int frame = 0; frame < Board::BetweenFrameMarginLength; frame ++)
				if( (j - Board::BoardStartY +2 )% (Board::FrameLength + Board::BetweenFrameMarginLength) == frame ) 
					gfx2.PutPixel( i, j, c );

		
		}
	}
}

