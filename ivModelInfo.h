class ivModelInfo
{
public:
	DWORD* getModel( int index )
	{
		typedef DWORD* ( __thiscall * vFuncFn )( void*, int );
		return vFunc<vFuncFn>( this, 1 )( this, index );
	}

	int	getModelIndex( const char* name )
	{
		typedef int( __thiscall * vFuncFn )( void*, const char* );
		return vFunc< vFuncFn >( this, 2 )( this, name );
	}

	const char* getModelName( const DWORD* model )
	{
		typedef const char* ( __thiscall * vFuncFn )( void*, const DWORD* );
		return vFunc< vFuncFn >( this, 3 )( this, model );
	}

	studiohdr_t* getStudioModel( const DWORD* mod )
	{
		typedef studiohdr_t* ( __thiscall * vFuncFn )( void*, const DWORD* );
		return vFunc< vFuncFn >( this, 28 )( this, mod );
	}
};