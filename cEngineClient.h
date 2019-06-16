class cEngineClient {
public:
	void clientCommand( const char* Command ) {
		typedef void( __thiscall * vFuncFn )( void*, const char* );
		vFunc<vFuncFn>( this, 7 )( this, Command );
	}

	void setViewAngles( Vector& ang )
	{
		return vFunc<void( __thiscall* )( void*, Vector& )>( this, 20 )( this, ang );
	}

	int getLocalPlayer( ) {
		typedef int( __thiscall * vFuncFn )( void* );
		return vFunc<vFuncFn>( this, 12 )( this );
	}

	bool isInGame( ) {
		typedef bool( __thiscall * vFuncFn )( void* );
		return vFunc<vFuncFn>( this, 26 )( this );
	}

	bool isConnected( ) {
		typedef bool( __thiscall * vFuncFn )( void* );
		return vFunc<vFuncFn>( this, 27 )( this );
	}

	void getPlayerInfo( int ent_num, player_info_t* pinfo )
	{
		typedef void( __thiscall * vFuncFn )( void*, int ent_num, player_info_t * pinfo );
		vFunc<vFuncFn>( this, 8 )( this, ent_num, pinfo );
	}

	bool isTakingScreenshot( ) {
		typedef bool( __thiscall * vFuncFn )( void* );
		return vFunc<vFuncFn>( this, 85 )( this );
	}

	void getViewAngles( Vector gay) {
		typedef void( __thiscall * vFuncFn )( void*, Vector );
		vFunc<vFuncFn>( this, 19 )( this, gay );
	}

	void clientCommandUnrestricted( const char* Command ) {
		typedef void( __thiscall * vFuncFn )( void*, const char* );
		vFunc<vFuncFn>( this, 106 )( this, Command );
	}

	int getMaxClients( void )
	{
		typedef int( __thiscall * vFuncFn )( PVOID );
		return vFunc<vFuncFn>( this, 21 )( this );
	}
};