class cDraw {
public:
	void outlinedRectangle( int x, int y, int w, int h, Color color );
	void filledRectangle( int x, int y, int w, int h, Color color );
	void Line( int x, int y, int x2, int y2, Color color );
	void String( int x, int y, unsigned long font, Color color, const char* text, bool centered = false );
	void intializeFonts( );

	void verticalGradient( int x, int y, int w, int h, Color startColor, Color endColor );

}; extern cDraw* Draw;

namespace Fonts {
	extern unsigned long mainFont;
	extern unsigned long tabFont;
}

enum fontFlags_T
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};