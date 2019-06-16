#pragma once

#pragma once

class Matrix4x4
{
public:
	float* operator[]( int i ) { return m[ i ]; }
	const float* operator[]( int i ) const { return m[ i ]; }

	float m[ 4 ][ 4 ];
};

class Vector2D
{
public:
	float x, y;

	constexpr explicit Vector2D( float _x = 0.f, float _y = 0.f ) : x( _x ), y( _y )
	{
	}

	constexpr explicit Vector2D( const float* v ) : x( v[ 0 ] ), y( v[ 1 ] )
	{
	}

	~Vector2D( )
	{
	}

	auto empty( ) const -> bool
	{
		return x == 0.f && y == 0.f;
	}

	auto clear( ) -> void
	{
		x = 0.f;
		y = 0.f;
	}

	auto operator==( const Vector2D& other ) const -> bool
	{
		return ( x == other.x && y == other.y );
	}

	auto operator!=( const Vector2D& other ) const -> bool
	{
		return !( *this == other );
	}

	template <typename A>
	auto operator+( A other ) const -> Vector2D
	{
		auto buf = *this;
		buf += static_cast< float >( other );
		return buf;
	}

	template <typename A>
	auto operator-( A other ) const -> Vector2D
	{
		auto buf = *this;
		buf -= static_cast< float >( other );
		return buf;
	}

	template <typename A>
	auto operator*( A other ) const -> Vector2D
	{
		auto buf = *this;
		buf *= static_cast< float >( other );
		return buf;
	}

	template <typename A>
	auto operator/( A other ) const -> Vector2D
	{
		auto buf = *this;
		buf /= static_cast< float >( other );
		return buf;
	}

	template <typename A>
	auto operator+=( A other ) -> Vector2D &



	{
		x += static_cast< float >( other );
		y += static_cast< float >( other );

		return *this;
	}

	template <typename A>
	auto operator-=( A other ) -> Vector2D &



	{
		x -= static_cast< float >( other );
		y -= static_cast< float >( other );

		return *this;
	}

	template <typename A>
	auto operator*=( A other ) -> Vector2D &



	{
		x *= static_cast< float >( other );
		y *= static_cast< float >( other );

		return *this;
	}

	template <typename A>
	auto operator/=( A other ) -> Vector2D &



	{
		x /= static_cast< float >( other );
		y /= static_cast< float >( other );

		return *this;
	}

	auto operator+( const Vector2D& other ) const -> Vector2D
	{
		auto buf = *this;

		buf.x += other.x;
		buf.y += other.y;

		return buf;
	}

	auto operator-( const Vector2D& other ) const -> Vector2D
	{
		auto buf = *this;

		buf.x -= other.x;
		buf.y -= other.y;

		return buf;
	}

	auto operator+=( const Vector2D& other ) -> Vector2D &



	{
		x += other.x;
		y += other.y;

		return ( *this );
	}

	auto operator-=( const Vector2D& other ) -> Vector2D &



	{
		x -= other.x;
		y -= other.y;

		return ( *this );
	}

	auto length( ) const -> float
	{
		return sqrt( length_sqr( ) );
	}

	auto length_sqr( ) const -> float
	{
		return x * x + y * y;
	}

	auto distance( const Vector2D& other ) const -> float
	{
		return ( other - ( *this ) ).length( );
	}

	auto normalize( ) -> void
	{
		*this /= length( );
	}

	auto normalized( ) const -> Vector2D
	{
		auto vec = *this;
		vec.normalize( );
		return vec;
	}

	friend std::ostream& operator<<( std::ostream& os, const Vector2D& v )
	{
		os << v.x << "\t" << v.y << std::endl;

		return os;
	}
};

class Vector
{
public:
	float x, y, z;

	constexpr explicit Vector( float _x = 0.f, float _y = 0.f, float _z = 0.f ) : x( _x ), y( _y ), z( _z )
	{
	}

	constexpr explicit Vector( const float* v ) : x( v[ 0 ] ), y( v[ 1 ] ), z( v[ 2 ] )
	{
	}

	~Vector( )
	{
	}

	auto empty( ) const -> bool
	{
		return x == 0.f && y == 0.f && z == 0.f;
	}

	auto clear( ) -> void
	{
		x = 0.f;
		y = 0.f;
		z = 0.f;
	}

	auto operator=( const Vector& other ) -> Vector &
	{
		x = other.x;
		y = other.y;
		z = 0.f;
		return *this;
	}

	auto operator==( const Vector& other ) const -> bool
	{
		return ( x == other.x && y == other.y && z == other.z );
	}

	auto operator!=( const Vector& other ) const -> bool
	{
		return !( *this == other );
	}

	template <typename A>
	auto operator+( A other ) const -> Vector
	{
		auto buf = *this;
		buf += static_cast< float >( other );
		return buf;
	}

	template <typename A>
	auto operator-( A other ) const -> Vector
	{
		auto buf = *this;
		buf -= static_cast< float >( other );
		return buf;
	}

	template <typename A>
	auto operator*( A other ) const -> Vector
	{
		auto buf = *this;
		buf *= static_cast< float >( other );
		return buf;
	}

	template <typename A>
	auto operator/( A other ) const -> Vector
	{
		auto buf = *this;
		buf /= static_cast< float >( other );
		return buf;
	}

	template <typename A>
	auto operator+=( A other ) -> Vector &
	{
		x += static_cast< float >( other );
		y += static_cast< float >( other );
		z += static_cast< float >( other );

		return *this;
	}

	template <typename A>
	auto operator-=( A other ) -> Vector &
	{
		x -= static_cast< float >( other );
		y -= static_cast< float >( other );
		z -= static_cast< float >( other );

		return *this;
	}

	template <typename A>
	auto operator*=( A other ) -> Vector &
	{
		x *= static_cast< float >( other );
		y *= static_cast< float >( other );
		z *= static_cast< float >( other );

		return *this;
	}

	template <typename A>
	auto operator/=( A other ) -> Vector &
	{
		x /= static_cast< float >( other );
		y /= static_cast< float >( other );
		z /= static_cast< float >( other );

		return *this;
	}

	auto operator+( const Vector& other ) const -> Vector
	{
		auto buf = *this;

		buf.x += other.x;
		buf.y += other.y;
		buf.z += other.z;

		return buf;
	}

	auto operator-( const Vector& other ) const -> Vector
	{
		auto buf = *this;

		buf.x -= other.x;
		buf.y -= other.y;
		buf.z -= other.z;

		return buf;
	}

	auto operator+=( const Vector& other ) -> Vector &
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return ( *this );
	}

	auto operator-=( const Vector& other ) -> Vector &
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return ( *this );
	}

	auto Length2D( ) const -> float
	{
		return sqrt( LengthSqr2D( ) );
	}

	auto LengthSqr2D( ) const -> float
	{
		return x * x + y * y;
	}

	auto Length( ) const -> float
	{
		return sqrt( LengthSqr( ) );
	}

	auto LengthSqr( ) const -> float
	{
		return x * x + y * y + z * z;
	}

	auto Size( ) const -> float
	{
		return sqrtf( this->x * this->x + this->y * this->y + this->z * this->z );
	}

	auto Distance( const Vector& other ) const -> float
	{
		return abs( ( other - *this ).Length( ) );
	}

	auto Normalize( ) -> void
	{
		*this /= Length( ) + std::numeric_limits<float>::epsilon( );
	}

	auto Normalized( ) const -> Vector
	{
		auto vec = *this;
		vec.Normalize( );
		return vec;
	}

	auto Dot( const Vector& other ) const -> float
	{
		return x * other.x + y * other.y + z * other.z;
	}

	auto Dot( float* other ) const -> float
	{
		return x * other[ 0 ] + y * other[ 1 ] + z * other[ 2 ];
	}

	friend std::ostream& operator<<( std::ostream& os, const Vector& v )
	{
		os << v.x << "\t" << v.y << "\t" << v.z << std::endl;

		return os;
	}
};

class Vector4D
{
public:
	float x, y, z, w;

	constexpr explicit Vector4D( float _x = 0.f, float _y = 0.f, float _z = 0.f, float _w = 0.f ) : x( _x ), y( _y ), z( _z ), w( _w )
	{
	}

	constexpr explicit Vector4D( const float* v ) : x( v[ 0 ] ), y( v[ 1 ] ), z( v[ 2 ] ), w( v[ 3 ] )
	{
	}

	~Vector4D( )
	{
	}

	auto empty( ) const -> bool
	{
		return x == 0.f && y == 0.f && z == 0.f && w == 0.f;
	}

	auto clear( ) -> void
	{
		x = 0.f;
		y = 0.f;
		z = 0.f;
		w = 0.f;
	}

	auto operator=( const Vector2D& other ) -> Vector4D &



	{
		x = other.x;
		y = other.y;
		z = 0.f;
		w = 0.f;
		return *this;
	}

	auto operator=( const Vector& other ) -> Vector4D &



	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = 0.f;
		return *this;
	}

	auto operator==( const Vector4D& other ) const -> bool
	{
		return ( x == other.x && y == other.y && z == other.z && w == other.w );
	}

	auto operator!=( const Vector4D& other ) const -> bool
	{
		return !( *this == other );
	}

	template <typename A>
	auto operator+( A other ) const -> Vector4D
	{
		auto buf = *this;
		buf += static_cast< float >( other );
		return buf;
	}

	template <typename A>
	auto operator-( A other ) const -> Vector4D
	{
		auto buf = *this;
		buf -= static_cast< float >( other );
		return buf;
	}

	template <typename A>
	auto operator*( A other ) const -> Vector4D
	{
		auto buf = *this;
		buf *= static_cast< float >( other );
		return buf;
	}

	template <typename A>
	auto operator/( A other ) const -> Vector4D
	{
		auto buf = *this;
		buf /= static_cast< float >( other );
		return buf;
	}

	template <typename A>
	auto operator+=( A other ) -> Vector4D &



	{
		x += static_cast< float >( other );
		y += static_cast< float >( other );
		z += static_cast< float >( other );
		w += static_cast< float >( other );

		return *this;
	}

	template <typename A>
	auto operator-=( A other ) -> Vector4D &



	{
		x -= static_cast< float >( other );
		y -= static_cast< float >( other );
		z -= static_cast< float >( other );
		w -= static_cast< float >( other );

		return *this;
	}

	template <typename A>
	auto operator*=( A other ) -> Vector4D &



	{
		x *= static_cast< float >( other );
		y *= static_cast< float >( other );
		z *= static_cast< float >( other );
		w *= static_cast< float >( other );

		return *this;
	}

	template <typename A>
	auto operator/=( A other ) -> Vector4D &



	{
		x /= static_cast< float >( other );
		y /= static_cast< float >( other );
		z /= static_cast< float >( other );
		w /= static_cast< float >( other );

		return *this;
	}

	auto operator+( const Vector4D& other ) const -> Vector4D
	{
		auto buf = *this;

		buf.x += other.x;
		buf.y += other.y;
		buf.z += other.z;
		buf.w += other.w;

		return buf;
	}

	auto operator-( const Vector4D& other ) const -> Vector4D
	{
		auto buf = *this;

		buf.x -= other.x;
		buf.y -= other.y;
		buf.z -= other.z;
		buf.w -= other.w;

		return buf;
	}

	auto operator+=( const Vector4D& other ) -> Vector4D &



	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return ( *this );
	}

	auto operator-=( const Vector4D& other ) -> Vector4D &



	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return ( *this );
	}

	auto length_2d( ) const -> float
	{
		return sqrt( length_sqr_2d( ) );
	}

	auto length_sqr_2d( ) const -> float
	{
		return x * x + y * y;
	}

	auto length_3d( ) const -> float
	{
		return sqrt( length_sqr_3d( ) );
	}

	auto length_sqr_3d( ) const -> float
	{
		return x * x + y * y + z * z;
	}

	auto length( ) const -> float
	{
		return sqrt( length_sqr( ) );
	}

	auto length_sqr( ) const -> float
	{
		return x * x + y * y + z * z + w * w;
	}

	auto distance( const Vector4D& other ) const -> float
	{
		return ( other - ( *this ) ).length( );
	}

	auto normalize( ) -> void
	{
		*this /= length( );
	}

	auto normalized( ) const -> Vector4D
	{
		auto vec = *this;
		vec.normalize( );
		return vec;
	}

	friend std::ostream& operator<<( std::ostream& os, const Vector4D& v )
	{
		os << v.x << "\t" << v.y << "\t" << v.z << "\t" << v.w << std::endl;

		return os;
	}
};

struct Matrix3x4
{
	Matrix3x4( ) {}
	Matrix3x4(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23 )
	{
		m_flMatVal[ 0 ][ 0 ] = m00;	m_flMatVal[ 0 ][ 1 ] = m01; m_flMatVal[ 0 ][ 2 ] = m02; m_flMatVal[ 0 ][ 3 ] = m03;
		m_flMatVal[ 1 ][ 0 ] = m10;	m_flMatVal[ 1 ][ 1 ] = m11; m_flMatVal[ 1 ][ 2 ] = m12; m_flMatVal[ 1 ][ 3 ] = m13;
		m_flMatVal[ 2 ][ 0 ] = m20;	m_flMatVal[ 2 ][ 1 ] = m21; m_flMatVal[ 2 ][ 2 ] = m22; m_flMatVal[ 2 ][ 3 ] = m23;
	}
	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	void Init( const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector& vecOrigin )
	{
		m_flMatVal[ 0 ][ 0 ] = xAxis.x; m_flMatVal[ 0 ][ 1 ] = yAxis.x; m_flMatVal[ 0 ][ 2 ] = zAxis.x; m_flMatVal[ 0 ][ 3 ] = vecOrigin.x;
		m_flMatVal[ 1 ][ 0 ] = xAxis.y; m_flMatVal[ 1 ][ 1 ] = yAxis.y; m_flMatVal[ 1 ][ 2 ] = zAxis.y; m_flMatVal[ 1 ][ 3 ] = vecOrigin.y;
		m_flMatVal[ 2 ][ 0 ] = xAxis.z; m_flMatVal[ 2 ][ 1 ] = yAxis.z; m_flMatVal[ 2 ][ 2 ] = zAxis.z; m_flMatVal[ 2 ][ 3 ] = vecOrigin.z;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	Matrix3x4( const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector& vecOrigin )
	{
		Init( xAxis, yAxis, zAxis, vecOrigin );
	}

	inline void SetOrigin( Vector const& p )
	{
		m_flMatVal[ 0 ][ 3 ] = p.x;
		m_flMatVal[ 1 ][ 3 ] = p.y;
		m_flMatVal[ 2 ][ 3 ] = p.z;
	}

	inline void Invalidate( void )
	{
		for ( int i = 0; i < 3; i++ ) {
			for ( int j = 0; j < 4; j++ ) {
				m_flMatVal[ i ][ j ] = std::numeric_limits<float>::infinity( );;
			}
		}
	}

	float* operator[]( int i ) { return m_flMatVal[ i ]; }
	const float* operator[]( int i ) const { return m_flMatVal[ i ]; }
	float* Base( ) { return &m_flMatVal[ 0 ][ 0 ]; }
	const float* Base( ) const { return &m_flMatVal[ 0 ][ 0 ]; }

	float m_flMatVal[ 3 ][ 4 ];
};
