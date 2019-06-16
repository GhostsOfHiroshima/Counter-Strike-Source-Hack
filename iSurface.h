class iSurface {
public:

	void drawSetColor( Color color ) {
		typedef void( __thiscall * vFuncFn )( void*, Color );
		vFunc<vFuncFn>( this, 10 )( this, color );
	}

	void drawFilledRect( int x, int y, int x2, int y2 ) {
		typedef void( __thiscall * vFuncFn )( void*, int, int, int, int );
		vFunc<vFuncFn>( this, 12 )( this, x, y, x2, y2 );
	}

	void drawOutlinedRectangle( int x, int y, int x2, int y2 ) {
		typedef void( __thiscall * vFuncFn )( void*, int, int, int, int );
		vFunc<vFuncFn>( this, 14 )( this, x, y, x2, y2 );
	}

	void drawLine( int x, int y, int x2, int y2 ) {
		typedef void( __thiscall * vFuncFn )( void*, int, int, int, int );
		vFunc<vFuncFn>( this, 15 )( this, x, y, x2, y2 );
	}

	void drawSetTextFont( unsigned long eFont )
	{
		typedef void( __thiscall * vFuncFn )( void*, unsigned long );
		return vFunc<vFuncFn>( this, 17 )( this, eFont );
	}

	void drawSetTextColor( int r, int g, int b, int a )
	{
		typedef void( __thiscall * vFuncFn )( void*, int, int, int, int );
		return vFunc<vFuncFn>( this, 19 )( this, r, g, b, a );
	}

	void drawSetTextPosition( int x, int y )
	{
		typedef void( __thiscall * vFuncFn )( void*, int, int );
		vFunc<vFuncFn>( this, 20 )( this, x, y );
	}

	void drawText( const wchar_t* chText, int iSize )
	{
		typedef void( __thiscall * vFuncFn )( void*, const wchar_t*, int, int );
		return vFunc<vFuncFn>( this, 22 )( this, chText, iSize, 0 );
	}

	void unlockCursor( )
	{
		typedef void( __thiscall * vFuncFn )( void* );
		return vFunc<vFuncFn>( this, 61 )( this );
	}

	void lockCursor( )
	{
		typedef void( __thiscall * vFuncFn )( void* );
		return vFunc<vFuncFn>( this, 62 )( this );
	}

	unsigned long createFont( )
	{
		typedef unsigned long( __thiscall * vFuncFn )( void* );
		return vFunc<vFuncFn>( this, 66 )( this );
	}

	void setFontGlypSet( unsigned long uFont, const char* chFontName, int iTall, int iWeight, int iFlags )
	{
		typedef void( __thiscall * vFuncFn )( void*, unsigned long, const char*, int, int, int, int, int, int, int );
		return vFunc<vFuncFn>( this, 67 )( this, uFont, chFontName, iTall, iWeight, 0, 0, iFlags, 0, 0 );
	}

	void getTextSize( DWORD font, const wchar_t* text, int& wide, int& tall )
	{
		typedef void( __thiscall * OriginalFn )( void*, DWORD, const wchar_t*, int&, int& );
		return vFunc< OriginalFn >( this, 75 )( this, font, text, wide, tall );
	}

};

class iEnginevGui {
public:

};

enum paintModeT
{
	PAINT_UIPANELS = ( 1 << 0 ),
	PAINT_INGAMEPANELS = ( 1 << 1 ),
	PAINT_CURSOR = ( 1 << 2 )
};
