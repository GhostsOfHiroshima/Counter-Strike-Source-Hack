struct model_t;
struct mstudiobbox_t
{
	int					bone;
	int					group;
	Vector				bbmin;
	Vector				bbmax;
	int					szhitboxnameindex;
	int					pad00[ 3 ];
	float				pillradius;
	int					pad01[ 4 ];
};

struct mstudiohitboxset_t
{
	int					sznameindex;
	inline char* const	pszName( void ) const { return ( (char* )this ) + sznameindex; }
	int					numhitboxes;
	int					hitboxindex;
	inline mstudiobbox_t* pHitbox( int i ) const { return (mstudiobbox_t* )( ( (BYTE* )this ) + hitboxindex ) + i; };
};

struct studiohdr_t
{
	BYTE				pad00[ 12 ];
	char				name[ 64 ];
	BYTE				pad01[ 80 ];
	int					numbones;
	int					boneindex;
	BYTE				pad02[ 12 ];
	int					hitboxsetindex;
	BYTE				pad03[ 228 ];

	// Look up hitbox set by index
	inline mstudiohitboxset_t* pHitboxSet( int i ) const
	{
		return (mstudiohitboxset_t* )( ( (BYTE* )this ) + hitboxsetindex ) + i;
	};

	// Calls through to hitbox to determine size of specified set
	inline mstudiobbox_t* pHitbox( int i, int set ) const
	{
		const mstudiohitboxset_t* s = pHitboxSet( set );
		if ( !s )
			return NULL;

		return s->pHitbox( i );
	};

	// Calls through to set to get hitbox count for set
	inline int			iHitboxCount( int set ) const
	{
		const mstudiohitboxset_t* s = pHitboxSet( set );
		if ( !s )
			return 0;

		return s->numhitboxes;
	};
};