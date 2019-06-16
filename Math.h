class cMath {
public:
	Vector vectorTransform( Vector In, Matrix3x4 Matrix );
	bool calculateBoxBounds( cBaseEntity* Entity, int& x, int& y, int& w, int& h );
	void vectorAngles( Vector& forward, Vector& angles );
	Vector calculateAngle( Vector& a, Vector& b );
	void sinCos( float r, float* s, float* c );
	void angleVectors( const Vector& angles, Vector* forward );
	float calculateFOVToVector( const Vector& viewAngle, const Vector& aimAngle );
	void vectorTransform( const Vector in1, float in2[ 3 ][ 4 ], Vector& out );
}; extern cMath* Math;