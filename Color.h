class Color
{
public:
	uint8_t r, g, b, a;

	constexpr explicit Color( uint8_t _r = 255, uint8_t _g = 255, uint8_t _b = 255, uint8_t _a = 255 ) : r( _r ), g( _g ), b( _b ), a( _a )
	{
	}

	constexpr explicit Color( const uint8_t* v ) : r( v[ 0 ] ), g( v[ 1 ] ), b( v[ 2 ] ), a( v[ 3 ] )
	{
	}

	~Color( )
	{
	}

	auto empty( ) const -> bool
	{
		return r == 0 && g == 0 && b == 0 && a == 0;
	}

	auto clear( ) -> void
	{
		r = 0;
		g = 0;
		b = 0;
		a = 0;
	}

	auto operator==( const Color& other ) const -> bool
	{
		return ( r == other.r && g == other.g && b == other.b && a == other.a );
	}

	auto operator!=( const Color& other ) const -> bool
	{
		return !( *this == other );
	}

	template <typename A>
	auto operator+( A other ) const -> Color
	{
		auto buf = *this;
		buf += static_cast< uint8_t >( other );
		return buf;
	}

	template <typename A>
	auto operator-( A other ) const -> Color
	{
		auto buf = *this;
		buf -= static_cast< uint8_t >( other );
		return buf;
	}

	template <typename A>
	auto operator*( A other ) const -> Color
	{
		auto buf = *this;
		buf *= static_cast< uint8_t >( other );
		return buf;
	}

	template <typename A>
	auto operator/( A other ) const -> Color
	{
		auto buf = *this;
		buf /= static_cast< uint8_t >( other );
		return buf;
	}

	template <typename A>
	auto operator+=( A other ) -> Color &



	{
		r += static_cast< uint8_t >( other );
		g += static_cast< uint8_t >( other );
		b += static_cast< uint8_t >( other );
		a += static_cast< uint8_t >( other );

		return *this;
	}

	template <typename A>
	auto operator-=( A other ) -> Color &



	{
		r -= static_cast< uint8_t >( other );
		g -= static_cast< uint8_t >( other );
		b -= static_cast< uint8_t >( other );
		a -= static_cast< uint8_t >( other );

		return *this;
	}

	template <typename A>
	auto operator*=( A other ) -> Color &
	{
		r *= static_cast< uint8_t >( other );
		g *= static_cast< uint8_t >( other );
		b *= static_cast< uint8_t >( other );
		a *= static_cast< uint8_t >( other );

		return *this;
	}

	template <typename A>
	auto operator/=( A other ) -> Color &
	{
		r /= static_cast< uint8_t >( other );
		g /= static_cast< uint8_t >( other );
		b /= static_cast< uint8_t >( other );
		a /= static_cast< uint8_t >( other );

		return *this;
	}

	auto operator+( const Color& other ) const -> Color
	{
		auto buf = *this;

		buf.r += other.r;
		buf.g += other.g;
		buf.b += other.b;
		buf.a += other.a;

		return buf;
	}

	auto operator-( const Color& other ) const -> Color
	{
		auto buf = *this;

		buf.r -= other.r;
		buf.g -= other.g;
		buf.b -= other.b;
		buf.a -= other.a;

		return buf;
	}

	auto operator+=( const Color& other ) -> Color &
	{
		r += other.r;
		g += other.g;
		b += other.b;
		a += other.a;

		return ( *this );
	}

	auto operator-=( const Color& other ) -> Color &
	{
		r -= other.r;
		g -= other.g;
		b -= other.b;
		a -= other.a;

		return ( *this );
	}

	template <typename T>
	Color hsvToRGB( T h, T s, T v ) const
	{
		int _r, _g, _b;

		if ( s != 0 )
		{
			int i;
			int f, p, q, t;

			h == 360 ? h = 0 : h = h / 60;
			i = static_cast< int >( trunc( h ) );
			f = h - i;

			p = v * ( 1 - s );
			q = v * ( 1 - s * f );
			t = v * ( 1 - s * ( 1 - f ) );

			switch ( i )
			{
			case 0:
				_r = v;
				_g = t;
				_b = p;
				break;

			case 1:
				_r = q;
				_g = v;
				_b = p;
				break;

			case 2:
				_r = p;
				_g = v;
				_b = t;
				break;

			case 3:
				_r = p;
				_g = q;
				_b = v;
				break;

			case 4:
				_r = t;
				_g = p;
				_b = v;
				break;

			default:
				_r = v;
				_g = p;
				_b = q;
				break;
			}
		}
		else
		{
			_r = v;
			_g = v;
			_b = v;
		}

		return Color( static_cast< uint8_t >( _r * 255 ), static_cast< uint8_t >( _g * 255 ), static_cast< uint8_t >( _b * 255 ) );
	}

	static Color hsbToRGB( float hue, float saturation, float brightness )
	{
		float h = hue == 1.0f ? 0 : hue * 6.0f;
		float f = h - (int )h;
		float p = brightness * ( 1.0f - saturation );
		float q = brightness * ( 1.0f - saturation * f );
		float t = brightness * ( 1.0f - ( saturation * ( 1.0f - f ) ) );

		if ( h < 1 )
		{
			return Color(
				(unsigned char )( brightness * 255 ),
				(unsigned char )( t * 255 ),
				(unsigned char )( p * 255 )
			);
		}
		else if ( h < 2 )
		{
			return Color(
				(unsigned char )( q * 255 ),
				(unsigned char )( brightness * 255 ),
				(unsigned char )( p * 255 )
			);
		}
		else if ( h < 3 )
		{
			return Color(
				(unsigned char )( p * 255 ),
				(unsigned char )( brightness * 255 ),
				(unsigned char )( t * 255 )
			);
		}
		else if ( h < 4 )
		{
			return Color(
				(unsigned char )( p * 255 ),
				(unsigned char )( q * 255 ),
				(unsigned char )( brightness * 255 )
			);
		}
		else if ( h < 5 )
		{
			return Color(
				(unsigned char )( t * 255 ),
				(unsigned char )( p * 255 ),
				(unsigned char )( brightness * 255 )
			);
		}
		else
		{
			return Color(
				(unsigned char )( brightness * 255 ),
				(unsigned char )( p * 255 ),
				(unsigned char )( q * 255 )
			);
		}
	}

	friend std::ostream& operator<<( std::ostream& os, const Color& v )
	{
		os << v.r << "\t" << v.g << "\t" << v.b << "\t" << v.a << std::endl;

		return os;
	}
};
