#include "Includes.h"

cConsole* Console;

void cConsole::Open( ) {
	AllocConsole( );
	freopen_s( (FILE * * )stdin, "CONIN$", "r", stdin );
	freopen_s( (FILE * * )stdout, "CONOUT$", "w", stdout );
}

void cConsole::Close( ) {
	fclose( (FILE* )stdin );
	fclose( (FILE* )stdout );
	HWND consoleHWND = GetConsoleWindow( );
	FreeConsole( );
	PostMessageW( consoleHWND, WM_CLOSE, 0, 0 );
}

void cConsole::Log( std::string Text )
{
	std::cout << Text << "\n";
}

void cConsole::logColor( std::string Text, consoleColors Color )
{
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

	SetConsoleTextAttribute( hConsole, Color );
	std::cout << Text << "\n";
	SetConsoleTextAttribute( hConsole, 15 );
}

void cConsole::logColor( const char Text, consoleColors Color )
{
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

	SetConsoleTextAttribute( hConsole, Color );
	std::cout << Text << "\n";
	SetConsoleTextAttribute( hConsole, 15 );
}
