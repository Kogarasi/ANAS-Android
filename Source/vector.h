
#ifndef __DEFINED_ANAS_VECTOR__
#define __DEFINED_ANAS_VECTOR__

#include <math.h>

namespace ANAS {

	class Vector2 {
		public:
			
			// Paramater
			float x;
			float y;

			// Operation

			Vector2():x(0),y(0){}
			Vector2( float _x, float _y )
				: x(_x), y(_y)
			{}

			
			Vector2 operator +( const Vector2 &v){
				return Vector2( this->x+ v.x, this->y+ v.y );
			}
			Vector2 operator -( const Vector2 &v){
				return Vector2( this->x- v.x, this->y- v.y );
			}
			Vector2 operator *( const float &f){
				return Vector2( this->x*f, this->y*f );
			}
			Vector2 operator /( const float &f){
				return Vector2( this->x/f, this->y/f );
			}

			inline float &operator []( const int &index ){
				switch( index ){
					case 0:
						return x;
					case 1:
						return y;
				}
				abort();
			}
			inline float length(){
				return sqrtf(x*x+y*y);
			}
	};
	class Vector3 {
		public:

			// Paramater
			float x;
			float y;
			float z;

			// Operation
			Vector3():x(0),y(0),z(0){}
			Vector3( float _x, float _y, float _z)
				: x(_x), y(_y), z(_z)
			{}
			
			Vector3 operator +( const Vector3 &v){
				return Vector3( this->x + v.x, this->y + v.y, this->z + v.z );
			}
			Vector3 operator -( const Vector3 &v){
				return Vector3( this->x - v.x, this->y - v.y, this->z - v.z );
			}
			Vector3 operator *( const float &f){
				return Vector3( this->x*f, this->y*f, this->z*f );
			}
			Vector3 operator /( const float &f){
				return Vector3( this->x/f, this->y/f, this->z/f );
			}

			inline float &operator []( const int &index ){
				switch( index ){
					case 0:
						return x;
					case 1:
						return y;
					case 2:
						return z;
				}
				abort();
			}

			inline float length(){
				return sqrtf(x*x+y*y+z*z);
			}
	};
	class Vector4 {
		public:

			// Paramater
			float x;
			float y;
			float z;
			float w;

			// Operation
			Vector4():x(0),y(0),z(0),w(0){}
			Vector4( float _x, float _y, float _z, float _w)
				: x(_x), y(_y), z(_z), w(_w)
			{}
			
			Vector4 operator +( const Vector4 &v){
				return Vector4( this->x + v.x, this->y + v.y, this->z + v.z, this->w + v.w );
			}
			Vector4 operator -( const Vector4 &v){
				return Vector4( this->x - v.x, this->y - v.y, this->z - v.z, this->w - v.w );
			}
			Vector4 operator *( const float &f){
				return Vector4( this->x*f, this->y*f, this->z*f, this->w*f );
			}
			Vector4 operator /( const float &f){
				return Vector4( this->x/f, this->y/f, this->z/f, this->w/f );
			}

			inline float &operator []( const int &index ){
				switch( index ){
					case 0:
						return x;
					case 1:
						return y;
					case 2:
						return z;
					case 3:
						return w;
				}
				abort();
			}

			inline float length(){
				return sqrtf(x*x+y*y+z*z+w*w);
			}
	};
}


#endif /* __DEFINED_ANAS_VECTOR__ */