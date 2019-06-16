#include "Includes.h"

cHooking* Hooking;

typedef void( __thiscall* paintFn )( void*, int );
typedef HRESULT( __stdcall* endSceneFn )( LPDIRECT3DDEVICE9 Device );
typedef void( __thiscall* lockCursorFn )( void* );
typedef bool( __thiscall* overrideViewFn )( void*, cViewSetup* );
typedef bool( __thiscall* createMoveFn )( void*, void*, float, cUserCmd* );

std::unique_ptr <VMT> vGuiHook;
std::unique_ptr <VMT> directXHook;
std::unique_ptr <VMT> iSurfaceHook;
std::unique_ptr <VMT> clientModeHook;

WNDPROC originalWndproc;

extern IMGUI_API LRESULT ImGui_ImplDX9_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

void __fastcall paintHooked( void* ecx, uintptr_t, int mode )
{
	static auto oPaint = vGuiHook->getOriginal<paintFn>( 13 );

	oPaint( ecx, mode );

	static bool hasnt_init_fonts = false;

	if ( !hasnt_init_fonts ) {
		Draw->intializeFonts( );
		hasnt_init_fonts = true;
	}

	static auto StartDrawing = reinterpret_cast< void( __thiscall* )( void* ) >( Utilities::hookManager->getSignature( "vguimatsurface.dll", "55 8B EC 64 A1 ? ? ? ? 6A FF 68 ? ? ? ? 50 64 89 25 ? ? ? ? 83 EC 14" ) );
	static auto FinishDrawing = reinterpret_cast< void( __thiscall* )( void* ) >( Utilities::hookManager->getSignature( "vguimatsurface.dll", "55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 64 89 25 ? ? ? ? 51 56 6A 00" ) );

	if ( mode & PAINT_INGAMEPANELS )
	{
		StartDrawing( I::Surface );

		FinishDrawing( I::Surface );
	}

	if ( mode & PAINT_UIPANELS )
	{
		StartDrawing( I::Surface );

		Visuals->Run( );
		Misc->locationSpam( );
		Misc->radioSpam( );
		Radar->Run( );

		static float colorAdd; colorAdd += 0.0005; if ( colorAdd > 1 ) colorAdd = 0;
		Draw->String( 0, 0, Fonts::mainFont, Color::hsbToRGB( colorAdd, 1.f, 1.f ), "WeebB0t" );

		auto localPlayer = I::entityList->getClientEntity( I::Engine->getLocalPlayer( ) );

		/*
		* Debug Information
		*/

		if ( localPlayer && localPlayer->isAlive( ) ) {
			std::string velocityDebug = "Velocity: " + std::to_string( (int )localPlayer->Velocity( ).Length2D( ) );
			std::string simulationTimeDebug = "Simulation Time: " + std::to_string( localPlayer->simulationTime( ) );
			std::string originDebug = "Origin: X: " + std::to_string( (int )localPlayer->Origin( ).x ) + " Y: " + std::to_string( (int )localPlayer->Origin( ).y ) + " Z: " + std::to_string( (int )localPlayer->Origin( ).z );
			std::string animationTimeDebug = "Animation Time: " + std::to_string( (int )localPlayer->animTime( ) );
			std::string vecMinsDebug = "vecMins: X: " + std::to_string( (int )localPlayer->vecMins( ).x ) + " Y: " + std::to_string( (int )localPlayer->vecMins( ).y ) + " Z: " + std::to_string( (int )localPlayer->vecMins( ).z );
			std::string vecMaxsDebug = "vecMaxs: X: " + std::to_string( (int )localPlayer->vecMaxs( ).x ) + " Y: " + std::to_string( (int )localPlayer->vecMaxs( ).y ) + " Z: " + std::to_string( (int )localPlayer->vecMaxs( ).z );
			std::string flagsDebug = "Flags: " + std::to_string( localPlayer->Flags( ) );
			std::string eyePositionDebug = "eyePosition: X: " + std::to_string( (int )localPlayer->eyePosition( ).x ) + " Y: " + std::to_string( (int )localPlayer->eyePosition( ).y ) + " Z: " + std::to_string( (int )localPlayer->eyePosition( ).z );
		//	Vector aimpunch = localPlayer + 0x6C;
			std::string punchAngleDebug = "punchAngle: X: " + std::to_string( localPlayer->punchAngle( ).x ) + " Y: " + std::to_string( localPlayer->punchAngle( ).y ) + " Z: " + std::to_string( localPlayer->punchAngle( ).z );

			Draw->String( 0, 15, Fonts::mainFont, Color( 255, 255, 255, 255 ), velocityDebug.c_str( ) );
			Draw->String( 0, 30, Fonts::mainFont, Color( 255, 255, 255, 255 ), simulationTimeDebug.c_str( ) );
			Draw->String( 0, 45, Fonts::mainFont, Color( 255, 255, 255, 255 ), originDebug.c_str( ) );
			Draw->String( 0, 60, Fonts::mainFont, Color( 255, 255, 255, 255 ), vecMinsDebug.c_str( ) );
			Draw->String( 0, 75, Fonts::mainFont, Color( 255, 255, 255, 255 ), vecMaxsDebug.c_str( ) );
			Draw->String( 0, 90, Fonts::mainFont, Color( 255, 255, 255, 255 ), flagsDebug.c_str( ) );
			Draw->String( 0, 105, Fonts::mainFont, Color( 255, 255, 255, 255 ), eyePositionDebug.c_str( ) );
			Draw->String( 0, 120, Fonts::mainFont, Color( 255, 255, 255, 255 ), punchAngleDebug.c_str( ) );
		}

		FinishDrawing( I::Surface );
	}
}

long __stdcall endSceneHooked( LPDIRECT3DDEVICE9 Device ) {
	static auto oEndScene = directXHook->getOriginal<endSceneFn>( 42 );

	static bool init = true;

	if ( init ) {
		ImGui_ImplDX9_Init( FindWindowW( L"Valve001", nullptr ), Device );
		Menu->Initialize( );
		init = false;
	}

	Device->SetRenderState( D3DRS_SRGBWRITEENABLE, FALSE );

	ImGui::GetIO( ).MouseDrawCursor = menuInfo::menuActive;

	ImGui_ImplDX9_NewFrame( );
	Menu->Run( );
	ImGui::Render( );

	return oEndScene( Device );
}

LRESULT __stdcall wndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {
	if ( uMsg == WM_KEYDOWN && wParam == VK_INSERT ) {
		menuInfo::menuActive = !menuInfo::menuActive;
		I::inputSystem->enableInput( !menuInfo::menuActive );
	}

	ImGui_ImplDX9_WndProcHandler( hWnd, uMsg, wParam, lParam );

	//if ( menuInfo::menuActive )
	//	return true;

	return CallWindowProcA( originalWndproc, hWnd, uMsg, wParam, lParam );
}

bool __fastcall overrideView( void* ecx, void* edx, cViewSetup* viewSetup )
{
	static auto oOverrideView = clientModeHook->getOriginal<overrideViewFn>( 16 );

	if ( Configuration::Visuals::View::fieldOfView > 0 ) {
		viewSetup->Fov = Configuration::Visuals::View::fieldOfView;
	}

	return oOverrideView( ecx, viewSetup );
}

void lockCursor( ) {
	static auto oLockCursor = iSurfaceHook->getOriginal<lockCursorFn>( 62 );

	if ( menuInfo::menuActive )
		I::Surface->unlockCursor( );
	else
		oLockCursor(I::Surface);
}

bool __fastcall createMove( void* ecx, void* edx, float inputSampleTime, cUserCmd* Cmd ) {
	auto localPlayer = I::entityList->getClientEntity( I::Engine->getLocalPlayer( ) );

	if ( Cmd->command_number == 0 || !localPlayer)
		return false;

	Misc->autoBunnyHop( Cmd );
	Misc->autoStrafe( Cmd );
	Aimbot->Run( Cmd );

	return false;
}

void cHooking::initializeHooks( ) {
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hConsole, consoleColors::Blue );

	vGuiHook = std::make_unique<VMT>( I::enginevGui );
	vGuiHook->Hook( 13, paintHooked );

	directXHook = std::make_unique<VMT>( I::directX );
	directXHook->Hook( 42, endSceneHooked );

	iSurfaceHook = std::make_unique<VMT>( I::Surface );
	iSurfaceHook->Hook( 62, lockCursor );

	clientModeHook = std::make_unique<VMT>( I::clientMode );
	clientModeHook->Hook( 16, overrideView );
	clientModeHook->Hook( 21, createMove );

	std::cout << "Hooked Paint: " << paintHooked << "\n";;
	std::cout << "Hooked endScene: " << endSceneHooked << "\n";
	std::cout << "Hooked overrideView: " << overrideView << "\n";
	std::cout << "Hooked createMove: " << createMove << "\n";

	if ( FindWindowW( L"Valve001", nullptr ) )        // Hook WNDProc to capture mouse / keyboard input
		originalWndproc = reinterpret_cast< WNDPROC >( SetWindowLongPtr( FindWindowW( L"Valve001", nullptr ), GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( wndProc ) ) );

	SetConsoleTextAttribute( hConsole, 15 );
}

void cHooking::unhookHooks( ) {
	vGuiHook->unhook( 13 );
	directXHook->unhook( 42 );
	iSurfaceHook->unhook( 62 );
	clientModeHook->unhook( 16 );
	SetWindowLongPtr( FindWindowW( L"Valve001", nullptr ), GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( originalWndproc ) );
}