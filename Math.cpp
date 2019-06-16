#include "Includes.h"

cMath* Math;

constexpr double pi = 3.14159265358979323846;

#define DEG2RAD( x )  ( (float)(x) * (float)( pi / 180.f ) )
#define RAD2DEG( x )  ( (float)(x) * (float)( 180.f / pi ) )

Vector cMath::vectorTransform( Vector In, Matrix3x4 Matrix ) {
	return Vector( In.Dot( Matrix[ 0 ] ) + Matrix[ 0 ][ 3 ], In.Dot( Matrix[ 1 ] ) + Matrix[ 1 ][ 3 ],
		In.Dot( Matrix[ 2 ] ) + Matrix[ 2 ][ 3 ] );
}

bool cMath::calculateBoxBounds( cBaseEntity* Entity, int& x, int& y, int& w, int& h ) {
	Matrix3x4& tran_frame = Entity->coordinateFrame( );

	Vector min = Entity->vecMins( );
	const Vector max = Entity->vecMaxs( );

	min.z += 10;

	Vector screen_boxes[ 8 ];

	Vector points[ ] = {
		Vector( min.x, min.y, min.z ),
		Vector( min.x, max.y, min.z ),
		Vector( max.x, max.y, min.z ),
		Vector( max.x, min.y, min.z ),
		Vector( max.x, max.y, max.z ),
		Vector( min.x, max.y, max.z ),
		Vector( min.x, min.y, max.z ),
		Vector( max.x, min.y, max.z )
	};

	for ( int i = 0; i <= 7; i++ )
		if ( !I::debugOverlay->screenPosition( vectorTransform( points[ i ], tran_frame ), screen_boxes[ i ] ) != 1 )
			return false;

	Vector box_array[ ] = {
		screen_boxes[ 3 ], // fl
		screen_boxes[ 5 ], // br
		screen_boxes[ 0 ], // bl
		screen_boxes[ 4 ], // fr
		screen_boxes[ 2 ], // fr
		screen_boxes[ 1 ], // br
		screen_boxes[ 6 ], // bl
		screen_boxes[ 7 ] // fl
	};

	float left = screen_boxes[ 3 ].x, bottom = screen_boxes[ 3 ].y, right = screen_boxes[ 3 ].x, top = screen_boxes[ 3 ].y;

	for ( int i = 0; i <= 7; i++ ) {
		if ( left > box_array[ i ].x )
			left = box_array[ i ].x;

		if ( bottom < box_array[ i ].y )
			bottom = box_array[ i ].y;

		if ( right < box_array[ i ].x )
			right = box_array[ i ].x;

		if ( top > box_array[ i ].y )
			top = box_array[ i ].y;
	}

	x = static_cast< int >( left );
	y = static_cast< int >( top );
	w = static_cast< int >( right ) - static_cast< int >( left );
	h = static_cast< int >( bottom ) - static_cast< int >( top );
	return true;
}


void cMath::vectorAngles( Vector& forward, Vector& angles ) {
	if ( forward.y == 0.0f && forward.x == 0.0f ) {
		angles.x = ( forward.z > 0.0f ) ? 270.0f : 90.0f;
		angles.y = 0.0f;
	}
	else {
		angles.x = atan2( -forward.z, Vector( forward ).Length( ) ) * -180 / static_cast< float >( pi );
		angles.y = atan2( forward.y, forward.x ) * 180 / static_cast< float >( pi );

		if ( angles.y > 90 )
			angles.y -= 180;
		else if ( angles.y < 90 )
			angles.y += 180;
		else if ( angles.y == 90 )
			angles.y = 0;
	}

	angles.z = 0.0f;
}

Vector cMath::calculateAngle( Vector& a, Vector& b ) {
	Vector angles;
	Vector delta;
	delta.x = ( a.x - b.x );
	delta.y = ( a.y - b.y );
	delta.z = ( a.z - b.z );

	double hyp = sqrt( delta.x * delta.x + delta.y * delta.y );
	angles.x = (float )( atanf( delta.z / hyp ) * 57.295779513082f );
	angles.y = (float )( atanf( delta.y / delta.x ) * 57.295779513082f );

	angles.z = 0.0f;
	if ( delta.x >= 0.0 ) { angles.y += 180.0f; }
	return angles;
}

void cMath::sinCos( float r, float* s, float* c ) {
	*s = sin( r );
	*c = cos( r );
}

void cMath::angleVectors( const Vector& angles, Vector* forward )
{
	float sp, sy, cp, cy;

	sinCos( DEG2RAD( angles.y ), &sy, &cy );
	sinCos( DEG2RAD( angles.x ), &sp, &cp );

	forward->x = cp * cy;
	forward->y = cp * sy;
	forward->z = -sp;
}


float cMath::calculateFOVToVector( const Vector& viewAngle, const Vector& aimAngle )
{
	Vector ang, aim;

	angleVectors( viewAngle, &aim );
	angleVectors( aimAngle, &ang );

	return RAD2DEG( acos( aim.Dot( ang ) / aim.LengthSqr( ) ) );
}

float dotProduct( Vector v1, Vector v2 )
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

void cMath::vectorTransform( const Vector in1, float in2[ 3 ][ 4 ], Vector& out )
{
	out.x = dotProduct( in1, Vector( in2[ 0 ][ 0 ], in2[ 0 ][ 1 ], in2[ 0 ][ 2 ] ) ) + in2[ 0 ][ 3 ];
	out.y = dotProduct( in1, Vector( in2[ 1 ][ 0 ], in2[ 1 ][ 1 ], in2[ 1 ][ 2 ] ) ) + in2[ 1 ][ 3 ];
	out.y = dotProduct( in1, Vector( in2[ 2 ][ 0 ], in2[ 2 ][ 1 ], in2[ 2 ][ 2 ] ) ) + in2[ 2 ][ 3 ];
}