/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Colors.h																			  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
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
#pragma once


class Color
{
public:
	unsigned int dword;
public:
	constexpr Color() : dword() {}
	constexpr Color( const Color& col )
		:
		dword( col.dword )
	{}
	constexpr Color( unsigned int dw )
		:
		dword( dw )
	{}
	constexpr Color( unsigned char x,unsigned char r,unsigned char g,unsigned char b )
		:
		dword( (x << 24u) | (r << 16u) | (g << 8u) | b )
	{}
	constexpr Color( unsigned char r,unsigned char g,unsigned char b )
		:
		dword( (r << 16u) | (g << 8u) | b )
	{}
	constexpr Color( Color col,unsigned char x )
		:
		Color( (x << 24u) | col.dword )
	{}
	Color& operator =( Color color )
	{
		dword = color.dword;
		return *this;
	}
	constexpr unsigned char GetX() const
	{
		return dword >> 24u;
	}
	constexpr unsigned char GetA() const
	{
		return GetX();
	}
	constexpr unsigned char GetR() const
	{
		return (dword >> 16u) & 0xFFu;
	}
	constexpr unsigned char GetG() const
	{
		return (dword >> 8u) & 0xFFu;
	}
	constexpr unsigned char GetB() const
	{
		return dword & 0xFFu;
	}
	void SetX( unsigned char x )
	{
		dword = (dword & 0xFFFFFFu) | (x << 24u);
	}
	void SetA( unsigned char a )
	{
		SetX( a );
	}
	void SetR( unsigned char r )
	{
		dword = (dword & 0xFF00FFFFu) | (r << 16u);
	}
	void SetG( unsigned char g )
	{
		dword = (dword & 0xFFFF00FFu) | (g << 8u);
	}
	void SetB( unsigned char b )
	{
		dword = (dword & 0xFFFFFF00u) | b;
	}
};

namespace Colors
{
	static constexpr Color MakeRGB( unsigned char r,unsigned char g,unsigned char b )
	{
		return (r << 16) | (g << 8) | b;
	}
	static constexpr Color PureWhite = MakeRGB( 220u,220u,220u );
	static constexpr Color White = MakeRGB( 170u,170u,170u );
	static constexpr Color Black = MakeRGB( 0u,0u,0u );
	static constexpr Color Gray = MakeRGB( 0x80u,0x80u,0x80u );
	static constexpr Color DarkLightGray = MakeRGB( 145u,148u,166u );
	static constexpr Color DarkGray = MakeRGB( 35u, 40u, 50u );
	static constexpr Color DarkGray2 = MakeRGB( 45u, 50u, 60u );
	static constexpr Color LightGray = MakeRGB( 0xD3u,0xD3u,0xD3u );
	static constexpr Color Red = MakeRGB( 255u,14u,41u );
	static constexpr Color Brown = MakeRGB( 197u,146u,129u );
	static constexpr Color Green = MakeRGB( 11u,171u,112u );
	static constexpr Color Wojtek = MakeRGB( 237u,227u,218u );
	static constexpr Color Lime = MakeRGB( 115u,235u,150u );
	static constexpr Color Pink = MakeRGB( 235u,130u,212u );
	static constexpr Color Blue = MakeRGB( 74u,126u,225u );
	static constexpr Color Yellow = MakeRGB( 255u,255u,0u );
	static constexpr Color Yellow2 = MakeRGB( 255u,216u,109u );
	static constexpr Color Cyan = MakeRGB( 75u,203u,252u );
	static constexpr Color Magenta = MakeRGB( 164u,123u,219u );
	static constexpr Color Orange = MakeRGB( 255u,154u,21u );
}