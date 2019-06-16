#include "Includes.h"

player_info_t cBaseEntity::getPlayerInfo( int Index )
{
	player_info_t pinfo;
	I::Engine->getPlayerInfo( Index, &pinfo );
	return pinfo;
}

std::string cBaseEntity::playerName( int Index )
{
	return this->getPlayerInfo( Index ).name;
}

bool cBaseEntity::setupBones( Matrix3x4* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime )
{
	PVOID pRenderable = (PVOID )( this + 0x4 );
	typedef bool( __thiscall * OriginalFn )( PVOID, Matrix3x4*, int, int, float );
	return vFunc<OriginalFn>( pRenderable, 16 )( pRenderable, pBoneToWorldOut, nMaxBones, boneMask, currentTime );
}

DWORD* cBaseEntity::getModel( )
{
	PVOID pRenderable = (PVOID )( this + 0x4 );
	typedef DWORD* ( __thiscall * vFuncFn )( PVOID );
	return vFunc<vFuncFn>( pRenderable, 9 )( pRenderable );
}

float DotProduct( const Vector& a, const Vector& b )
{
	return ( a.x * b.x + a.y * b.y + a.z * b.z );
}

void VectorTransform( const Vector in1, Matrix3x4 in2, Vector& out )
{
	out.x = DotProduct( in1, Vector( in2[ 0 ][ 0 ], in2[ 0 ][ 1 ], in2[ 0 ][ 2 ] ) ) + in2[ 0 ][ 3 ];
	out.y = DotProduct( in1, Vector( in2[ 1 ][ 0 ], in2[ 1 ][ 1 ], in2[ 1 ][ 2 ] ) ) + in2[ 1 ][ 3 ];
	out.z = DotProduct( in1, Vector( in2[ 2 ][ 0 ], in2[ 2 ][ 1 ], in2[ 2 ][ 2 ] ) ) + in2[ 2 ][ 3 ];
}

Vector cBaseEntity::getBonePosition(int bone )
{
	Matrix3x4 boneMatrix[ 128 ];

	if ( this->setupBones( boneMatrix, 128, 0x00000100, 0 ) )
		return Vector( boneMatrix[ bone ][ 0 ][ 3 ], boneMatrix[ bone ][ 1 ][ 3 ], boneMatrix[ bone ][ 2 ][ 3 ] );

	return Vector( 0, 0, 0 );
}

Vector cBaseEntity::punchAngle( ) {
	return *reinterpret_cast< Vector* >( uintptr_t( this ) + 0x0DDC/* m_Local*/ + 0x6C );
}