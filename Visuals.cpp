#include "Includes.h"

cVisuals* Visuals;

void cVisuals::Run( ) {
	auto localPlayer = I::entityList->getClientEntity( I::Engine->getLocalPlayer( ) );
	for ( int i = 1; i < I::Engine->getMaxClients( ); i++ ) {
		auto Entity = I::entityList->getClientEntity( i );

		if ( !Entity || Entity->isDormant( ) || !Entity->isAlive( ) || Entity->Team( ) == localPlayer->Team( ) )
			continue;

		int x, y, w, h;

		if ( Math->calculateBoxBounds( Entity, x, y, w, h ) ) {

			if ( Configuration::Visuals::Player::Name )
				Draw->String( x + ( w / 2 ), y - 14, Fonts::mainFont, Color( 255, 255, 255, 255 ), Entity->playerName( i ).c_str( ), true );

			if ( Configuration::Visuals::Player::Box ) {
				Draw->outlinedRectangle( x, y, w, h, Color( 255, 239, 4, 255 ) );
				Draw->outlinedRectangle( x - 1, y - 1, w + 2, h + 2, Color( 0, 0, 0, 255 ) );
				Draw->outlinedRectangle( x + 1, y + 1, w - 2, h - 2, Color( 0, 0, 0, 255 ) );
			}

			if ( Configuration::Visuals::Player::Health ) {
				Draw->filledRectangle( x, y + h + 2, ( Entity->Health( ) * w ) / 100, 4, Color( 0, 255, 0, 255 ) );
				Draw->outlinedRectangle( x - 1, y + h + 2, w + 2, 4, Color( 0, 0, 0, 255 ) );
			}
		}
	}
}