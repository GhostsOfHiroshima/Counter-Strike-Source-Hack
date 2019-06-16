#include "Includes.h"

cMisc* Misc;

void cMisc::locationSpam( ) {
	if ( !Configuration::Misc::Spam::locationSpam )
		return;

	auto localPlayer = I::entityList->getClientEntity( I::Engine->getLocalPlayer( ) );

	for ( int i = 1; i < I::entityList->getHighestEntityIndex( ); i++ ) {
		auto Entity = I::entityList->getClientEntity( i );

		if ( !Entity || !Entity->isAlive( ) || Entity->isDormant( ) )
			continue;

		if ( Entity->playerName( i ) == "" )
			continue;

		if ( Entity == localPlayer )
			continue;

		std::string Command; Command = "Say [WeebB0t] " + Entity->playerName( i ) + " is located at " + Entity->getLastPlace( );
		I::Engine->clientCommand( Command.c_str( ) );
	}
}

void cMisc::radioSpam( ) {
	if ( !Configuration::Misc::Spam::radioSpam )
		return;

	static int storedTime;

	storedTime++;

	if ( storedTime > Configuration::Misc::Spam::radioSpamDelay ) {
		I::Engine->clientCommand( "getout" );
		storedTime = 0;
	}
}

void cMisc::noSpread( cUserCmd* Cmd ) {
}

void cMisc::autoBunnyHop( cUserCmd* Cmd ) {
	if ( !Configuration::Misc::Movement::autoBunnyhop )
		return;

	static bool lastJumped = false;
	static bool Fake = false;

	auto localPlayer = I::entityList->getClientEntity( I::Engine->getLocalPlayer( ) );

	if ( !( localPlayer->Flags( ) & FL_ONGROUND ) && Cmd->buttons & IN_JUMP ) {
			Cmd->buttons &= ~IN_JUMP;
	}
		
}

void cMisc::autoStrafe( cUserCmd* Cmd ) {
	if ( !Configuration::Misc::Movement::autoStrafe )
		return;

	auto localPlayer = I::entityList->getClientEntity( I::Engine->getLocalPlayer( ) );

	if ( !( localPlayer->Flags( ) & FL_ONGROUND ) ) {
		if ( Cmd->mousedx < 0 ) Cmd->sidemove = -450.0f;
		if ( Cmd->mousedx > 0 ) Cmd->sidemove = 450.0f;
	}
}
