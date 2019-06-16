class cDebugOverlay
{
public:
	int screenPosition( const Vector& point, Vector& screen ) {
		typedef int( __thiscall * vFuncFn )( void*, const Vector&, Vector& );
		return vFunc<vFuncFn>( this, 10 )( this, point, screen );
	}
};