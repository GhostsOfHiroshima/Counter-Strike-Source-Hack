#include "Includes.h"

cRadar* Radar;

int radarSize = 200, radarX = 30, radarY = 30;

Vector2D getMousePosition( )
{
	POINT mousePosition;
	GetCursorPos( &mousePosition );
	ScreenToClient( FindWindow( 0, "Counter-Strike Source" ), &mousePosition );
	return { Vector2D( static_cast< float >( mousePosition.x ), static_cast< float >( mousePosition.y ) ) };
}

bool mouseInArea( int x, int y, int x2, int y2 ) {
	if ( getMousePosition( ).x > x && getMousePosition( ).y > y && getMousePosition( ).x < x2 + x && getMousePosition( ).y < y2 + y )
		return true;
	return false;
}

void cRadar::Run( ) {

	if ( !Configuration::Visuals::Radar::radarEnabled )
		return;

	radarSize = Configuration::Visuals::Radar::radarSize;

	this->handlePosition( );
	this->Render( );
}

void cRadar::Render( ) {

	/*
	* Handle regular drawing
	*/

	Draw->filledRectangle( radarX, radarY, radarSize, radarSize, Color( 125, 125, 125, 255 ) );
	Draw->outlinedRectangle( radarX, radarY, radarSize, radarSize, Color( 0, 0, 0, 255 ) );

	for ( int i = 0; i < radarSize / 5; i++ )
		Draw->filledRectangle( radarX, radarY + ( i * 5 ), radarSize, 1, Color( 0, 0, 0, 145 ) );
	for ( int i = 0; i < radarSize / 5; i++ )
		Draw->filledRectangle( radarX + ( i * 5 ), radarY, 1, radarSize, Color( 0, 0, 0, 145 ) );

	Draw->filledRectangle( radarX, radarY + ( radarSize / 2 ), radarSize, 1, Color( 0, 0, 0, 255 ) );
	Draw->filledRectangle( radarX + ( radarSize / 2 ), radarY, 1, radarSize, Color( 0, 0, 0, 255 ) );
	Draw->filledRectangle( radarX + ( radarSize / 2 ) - 2, radarY + ( radarSize / 2 ) - 2, 4, 4, Color( 255, 255, 255, 255 ) );

	/*
	* Handle player point drawing
	*/


	for ( int i = 1; i < I::entityList->getHighestEntityIndex( ); i++ ) {

		auto Entity = I::entityList->getClientEntity( i );

		if ( !Entity )
			continue;

		auto localPlayer = I::entityList->getClientEntity( I::Engine->getLocalPlayer() );

		if ( !localPlayer )
			return;

		if ( !Entity || Entity->isDormant( ) || !Entity->isAlive( ) || Entity == localPlayer )
			continue;
	}
}


void cRadar::handlePosition( ) {
	static Vector2D offsetDrag;
	static bool shouldBeDragging;

	if ( GetAsyncKeyState( VK_LBUTTON ) && mouseInArea( radarX, radarY, radarSize, radarSize ) )
		shouldBeDragging = true;

	if ( !GetAsyncKeyState( VK_LBUTTON ) )
		shouldBeDragging = false;

	if ( shouldBeDragging ) {
		radarX = getMousePosition( ).x - offsetDrag.x;
		radarY = getMousePosition( ).y - offsetDrag.y;
	}

	if ( mouseInArea( radarX, radarY, radarSize, radarSize ) ) {
		offsetDrag.x = getMousePosition( ).x - radarX;
		offsetDrag.y = getMousePosition( ).y - radarY;
	}
}