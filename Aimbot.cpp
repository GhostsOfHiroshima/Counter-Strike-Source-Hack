#include "Includes.h"

cAimbot* Aimbot;

/*
* Layout of how this is going to work
* Functions: Run -> Find Target -> Aim at target -> Remove inaccuracies (recoil / spread)
*/

void cAimbot::Run( cUserCmd* Cmd ) {
	if ( !Configuration::Aimbot::aimbotEnabled )
		return;

	auto localPlayer = I::entityList->getClientEntity( I::Engine->getLocalPlayer( ) );

	if ( !localPlayer || !localPlayer->isAlive( ) )
		return;

	if ( findTarget( ) != -1 ) {
		aimAtTarget( Cmd );
	}

	removeInaccuracies( Cmd );
}

int cAimbot::findTarget() {
	auto localPlayer = I::entityList->getClientEntity( I::Engine->getLocalPlayer( ) );

	for ( int i = 1; i < I::Engine->getMaxClients( ); i++ ) {
		auto Entity = I::entityList->getClientEntity( i );

		if ( !Entity || !Entity->isAlive( ) || Entity->isDormant( ) || Entity->Team() == localPlayer->Team() )
			continue;

		return i;
	}

	return -1;
}

void cAimbot::aimAtTarget( cUserCmd* Cmd ) {
	auto Target = I::entityList->getClientEntity( findTarget( ) );
	auto localPlayer = I::entityList->getClientEntity( I::Engine->getLocalPlayer( ) );

	auto entityBonePosition = Target->getBonePosition( Configuration::Aimbot::aimBone );
	auto eyePosition = localPlayer->eyePosition( );
	
	auto aimPosition = Math->calculateAngle( eyePosition, entityBonePosition );

	if ( GetAsyncKeyState( VK_MENU ) || Configuration::Aimbot::autoAim) {
		Cmd->viewangles = aimPosition;

		if ( !Configuration::Aimbot::silentAim )
			I::Engine->setViewAngles( Cmd->viewangles );

		if ( Configuration::Aimbot::autoFire )
			Cmd->buttons |= IN_ATTACK;
	}
}

void cAimbot::removeInaccuracies( cUserCmd* Cmd ) {
	auto localPlayer = I::entityList->getClientEntity( I::Engine->getLocalPlayer( ) );

	if ( Configuration::Aimbot::noRecoil )
		Cmd->viewangles -= localPlayer->punchAngle( ) * 2;
}