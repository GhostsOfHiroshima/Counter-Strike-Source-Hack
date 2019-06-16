#include "Includes.h"

BOOL WINAPI Initialize( HINSTANCE Module ) {
	Console->Open( );
	Console->Log( "Hi :)" );
	interfaceUtils->findInterfaces( );
	Hooking->initializeHooks( );

	while ( !GetAsyncKeyState( VK_END ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 120 ) );

	Hooking->unhookHooks( );
	std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );

	Console->Close( );

	FreeLibraryAndExitThread( Module, EXIT_SUCCESS );
}

BOOL WINAPI DllMain( HINSTANCE Module, DWORD Reason, LPVOID Reserved )
{
	if ( Reason == DLL_PROCESS_ATTACH ) {
		CreateThread( nullptr, NULL, (LPTHREAD_START_ROUTINE )Initialize, Module, NULL, nullptr );
	}

	return TRUE;
}