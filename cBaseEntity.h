typedef struct player_info_s {
	char			name[ 32 ];
	int				userID;
	char			guid[ 32 + 1 ];
	long			friendsID;
	char			friendsName[ 32 ];
	bool			fakeplayer;
	bool			ishltv;
	int				customFiles[ 4 ];
	unsigned char	filesDownloaded;
} player_info_t;

class cBaseEntity {
public:
	int Health( ) {
		return *reinterpret_cast< int* >( uintptr_t( this ) + 0x94 );
	}

	int Armor( ) {
		return *reinterpret_cast< int* >( uintptr_t( this ) + 0x1498 );
	}

	int Flags( ) {
		return *reinterpret_cast< int* >( uintptr_t( this ) + 0x350 );
	}

	int Team( ) {
		return *reinterpret_cast< int* >( uintptr_t( this ) + 0x9C );
	}

	float simulationTime( ) {
		return *reinterpret_cast< float* >( uintptr_t( this ) + 0x6C );
	}

	float animTime( ) {
		return *reinterpret_cast< float* >( uintptr_t( this ) + 0x4 + 0x64 );
	}

	byte lifeState( ) {
		return *reinterpret_cast< byte* >( uintptr_t( this ) + 0x93 );
	}

	Vector Velocity( ) {
		return *reinterpret_cast< Vector* >( uintptr_t( this ) + 0xF4 ); // 0x13c
	}

	bool isAlive( )
	{
		return this->lifeState( ) == 0;
	}

	bool isDormant( ) {
		return *reinterpret_cast< bool* >( uintptr_t( this ) + 0x17E );
	}

	Vector Origin( ) {
		return *reinterpret_cast< Vector* >( uintptr_t( this ) + 0x290 );
	}

	Vector viewOffset( ) {
		return *reinterpret_cast< Vector* >( uintptr_t( this ) + 0x0E8 );
	}

	Vector eyePosition( ) {
		return this->absOrigin() + *reinterpret_cast< Vector* >( uintptr_t( this ) + 0x0E8 );
	}
	
	Vector vecMins( ) {
		return *reinterpret_cast< Vector* >( uintptr_t( this ) + 0x19c /*m_Collision*/ + 0x2C );
	}

	Vector vecMaxs( ) {
		return *reinterpret_cast< Vector* >( uintptr_t( this ) + 0x19c /*m_Collision*/ + 0x20 );
	}

	uint32_t hitboxSet( ) {
		return *reinterpret_cast< uint32_t* >( uintptr_t( this ) + 0x528 );
	}

	std::string getLastPlace( )
	{
		return std::string( (const char* )this + 0x125C );
	}
	
	Matrix3x4& coordinateFrame( ) {
		PVOID pRenderable = static_cast< PVOID >( this + 0x4 );
		typedef Matrix3x4& ( __thiscall * OriginalFn )( PVOID );
		return vFunc<OriginalFn>( pRenderable, 34 )( pRenderable );
	}

	Vector& absOrigin( )
	{
		typedef Vector& ( __thiscall * vFuncFn )( PVOID );
		return vFunc<vFuncFn>( this, 9 )( this );
	}


	player_info_t getPlayerInfo( int Index );

	std::string playerName( int Index );
	bool setupBones( Matrix3x4* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime );
	DWORD* getModel( );
	Vector punchAngle( );
	Vector getBonePosition( int bone );
};