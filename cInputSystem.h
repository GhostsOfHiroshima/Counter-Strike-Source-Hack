class cInputSystem {
public:
	void enableInput( bool Enabled )
	{
		typedef void( __thiscall * vFuncFn )( void*, bool );
		return vFunc<vFuncFn>( this, 7 )( this, Enabled );
	}
};