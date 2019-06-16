using interfaceFn = void* ( * )( );
class interfaceRegistration {
public:
	interfaceRegistration( ) = delete;

	interfaceFn            create_fn;
	const char* name;
	interfaceRegistration* next;
};

template<typename T>
static T* captureInterface( const char* Mod, const char* iFace, bool Exact = false ) {
	T* Interface = nullptr;
	interfaceRegistration* registerList;
	int partMatchLen = strlen( iFace );

	DWORD interfaceFn = reinterpret_cast< DWORD >( GetProcAddress( GetModuleHandleA( Mod ), "CreateInterface" ) );
	if ( !interfaceFn ) { return nullptr; }

	unsigned int jumpStart = (unsigned int )(interfaceFn )+4;
	unsigned int jumpTarget = jumpStart + *(unsigned int* )( jumpStart + 1 ) + 5;

	registerList = **reinterpret_cast< interfaceRegistration * ** >( jumpTarget + 6 );

	for ( interfaceRegistration* Cur = registerList; Cur; Cur = Cur->next ) {
		if ( Exact ) {
			if ( strcmp( Cur->name, iFace ) == 0 )
				Interface = reinterpret_cast< T* >( Cur->create_fn( ) );
		}
		else {
			if ( !strncmp( Cur->name, iFace, partMatchLen ) && std::atoi( Cur->name + partMatchLen ) > 0 )
				Interface = reinterpret_cast< T* >( Cur->create_fn( ) );
		}
	}

	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

	SetConsoleTextAttribute( hConsole, consoleColors::Blue );
	std::cout << Interface << "\n";
	SetConsoleTextAttribute( hConsole, 15 );

	return Interface;
}

class cInterfaces {
public:
	void findInterfaces( );

private:
	void* retrieveInterface( const char* Module, const char* Name );
	typedef void* ( *retrieveInterfaceFn ) ( const char* name, int* return_code );

}; extern cInterfaces* interfaceUtils;

namespace I {
	extern cEngineClient* Engine;
	extern iSurface* Surface;
	extern iEnginevGui* enginevGui;
	extern IDirect3DDevice9* directX;
	extern cInputSystem* inputSystem;
	extern void* clientMode;
	extern void* Client;
	extern cClientEntityList* entityList;
	extern cDebugOverlay* debugOverlay;
	extern ivModelInfo* modelInfo;
}

namespace Utilities {
	extern cHookManager* hookManager;
}