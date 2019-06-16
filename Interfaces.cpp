#include "Includes.h"
cInterfaces* interfaceUtils;

cEngineClient* I::Engine = nullptr;
iSurface* I::Surface = nullptr;
iEnginevGui* I::enginevGui = nullptr;
IDirect3DDevice9* I::directX = nullptr;
cInputSystem* I::inputSystem = nullptr;
void* I::clientMode = nullptr;
void* I::Client = nullptr;
cClientEntityList* I::entityList = nullptr;
cDebugOverlay* I::debugOverlay = nullptr;
ivModelInfo* I::modelInfo = nullptr;

cHookManager* Utilities::hookManager = new cHookManager;

void cInterfaces::findInterfaces( ) {
	I::Client = captureInterface<void>( "client", "VClient" );
	I::Engine = captureInterface<cEngineClient>( "engine", "VEngineClient" );
	I::Surface = captureInterface<iSurface>( "vguimatsurface", "VGUI_Surface" );
	I::enginevGui = captureInterface<iEnginevGui>( "engine", "VEngineVGui" );
	I::directX = **(IDirect3DDevice9 * ** )( Utilities::hookManager->getSignature( "shaderapidx9.dll", "55 8B EC 51 56 8B F1 83 7E 24 00" ) + 0x2B );
	I::inputSystem = captureInterface<cInputSystem>( "inputsystem", "InputSystemVersion" );
	I::clientMode = **(void*** )( ( *(uintptr_t * * )I::Client )[ 10 ] + 0x5 );
	I::entityList = captureInterface<cClientEntityList>( "client", "VClientEntityList" );
	I::debugOverlay = captureInterface<cDebugOverlay>( "engine", "VDebugOverlay" );
	I::modelInfo = captureInterface<ivModelInfo>( "engine", "VModelInfoClient" );
}