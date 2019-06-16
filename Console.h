
enum consoleColors {
	darkBlue = 1,
	darkGreen,
	darkCyan,
	darkRed,
	darkPink,
	darkYellow,
	darkWhite,
	darkGray,
	Blue,
	Green,
	Cyan,
	Red,
	Pink,
	Yellow,
	White
};

class cConsole {
public:
	void Open( );
	void Close( );
	void Log( std::string Text );
	void logColor( std::string Text, consoleColors Color );
	void logColor( const char Text, consoleColors Color );
}; extern cConsole* Console;