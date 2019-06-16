class cHookManager
{
public:
	template <typename T>
	static T Hook( void* pOriginal, void* pNew, int iIndex );
	static MODULEINFO getModuleInfo( char* szModule );
	DWORD findPattern( DWORD dwAddress, DWORD dwLength, const char* szPattern );
	DWORD getSignature( const char* szModuleName, const char* szPattern );
};

template <typename T>
T vFunc( void* pAddress, int iIndex )
{
	return ( *reinterpret_cast< T * * >( pAddress ) )[ iIndex ];
}

class VMT {
private:

	std::unique_ptr<std::uintptr_t[ ]> p_newvmt = nullptr;
	std::uintptr_t** p_baseclass = nullptr;
	std::uintptr_t* p_ogvmt = nullptr;
	std::size_t                       index_count = 0;

public:

	VMT( void* pp_class ) {

		this->p_baseclass = static_cast < std::uintptr_t * * > ( pp_class );

		while ( static_cast < std::uintptr_t* > ( *this->p_baseclass )[ this->index_count ] )
			++this->index_count;

		const std::size_t size_table = this->index_count * sizeof( std::uintptr_t );

		this->p_ogvmt = *this->p_baseclass;
		this->p_newvmt = std::make_unique < std::uintptr_t[ ] >( this->index_count );

		std::memcpy( this->p_newvmt.get( ), this->p_ogvmt, size_table );

		*this->p_baseclass = this->p_newvmt.get( );

	};
	~VMT( ) { *this->p_baseclass = this->p_ogvmt; };

	template<class T>
	T getOriginal( const std::size_t index ) {

		return reinterpret_cast < T > ( this->p_ogvmt[ index ] );

	};

	HRESULT Hook( const std::size_t index, void* fn_new ) {

		if ( index > this->index_count )
			return E_INVALIDARG;

		this->p_newvmt[ index ] = reinterpret_cast < std::uintptr_t > ( fn_new );
		return S_OK;

	};

	HRESULT unhook( const std::size_t index ) {

		if ( index > this->index_count )
			return E_INVALIDARG;

		this->p_newvmt[ index ] = this->p_ogvmt[ index ];
		return S_OK;

	};

};