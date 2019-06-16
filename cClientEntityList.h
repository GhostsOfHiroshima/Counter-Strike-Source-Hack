class cBaseHandle;
class iClientNetworkable;

class cClientEntityList {
public:
	virtual ~cClientEntityList( );
	virtual iClientNetworkable* getClientNetworkable( int ) = 0;
	virtual iClientNetworkable* getClientNetworkableFromHandle( HANDLE ) = 0;
	virtual cBaseEntity* getClientEntity( int ) = 0;
	virtual cBaseEntity* getClientEntityFromHandle( HANDLE ) = 0;
	virtual int					numberOfEntities( bool ) = 0;
	virtual int					getHighestEntityIndex( void ) = 0;
	virtual void				getMaxEntities( int ) = 0;
	virtual int					getMaxEntities( ) = 0;
};