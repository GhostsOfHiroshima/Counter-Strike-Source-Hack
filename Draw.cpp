#include "Includes.h"

cDraw* Draw;

unsigned long Fonts::mainFont;
unsigned long Fonts::tabFont;

void cDraw::outlinedRectangle( int x, int y, int w, int h, Color color ) {
	I::Surface->drawSetColor( color );
	I::Surface->drawOutlinedRectangle( x, y, x + w, y + h );
}

void cDraw::filledRectangle( int x, int y, int w, int h, Color color ) {
	I::Surface->drawSetColor( color );
	I::Surface->drawFilledRect( x, y, x + w, y + h );
}

void cDraw::Line( int x, int y, int x2, int y2, Color color ) {
	I::Surface->drawSetColor( color );
	I::Surface->drawLine( x, y, x2, y2 );
}

void cDraw::String( int x, int y, unsigned long font, Color color, const char* text, bool centered) {
	size_t o_Size = strlen( text ) + 1;
	const size_t n_Size = 1024;
	size_t convertedChars = 0;
	wchar_t wcstring[ n_Size ];
	mbstowcs_s( &convertedChars, wcstring, o_Size, text, _TRUNCATE );

	int width, height;
	I::Surface->getTextSize( font, wcstring, width, height );

	if ( centered )
		x -= width / 2;


	I::Surface->drawSetTextFont( font );
	I::Surface->drawSetTextColor( color.r, color.g, color.b, color.a );
	I::Surface->drawSetTextPosition( x, y );
	I::Surface->drawText( wcstring, wcslen( wcstring ) );
}

void cDraw::intializeFonts( ) {
	Fonts::mainFont = I::Surface->createFont( );
	Fonts::tabFont = I::Surface->createFont( );

	I::Surface->setFontGlypSet( Fonts::mainFont, "Verdana", 12, 400, FONTFLAG_DROPSHADOW );
	I::Surface->setFontGlypSet( Fonts::tabFont, "Exonence", 42, 200, FONTFLAG_DROPSHADOW | FONTFLAG_ANTIALIAS );
}

void cDraw::verticalGradient( int x, int y, int w, int h, Color startColor, Color endColor )
{
	filledRectangle( x, y, w, h, startColor );
	BYTE first = endColor.r;
	BYTE second = endColor.g;
	BYTE third = endColor.b;
	for ( int i = 0; i < h; i++ )
	{
		float fi = i, fh = h;
		float a = fi / fh;
		DWORD ia = a * 255;
		filledRectangle( x, y + i, w, 1, Color( first, second, third, ia ) );
	}
}