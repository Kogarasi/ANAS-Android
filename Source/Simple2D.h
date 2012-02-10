
#ifndef __DEFINED_SHADER_SIMPLE2D__
#define __DEFINED_SHADER_SIMPLE2D__

#include <GLES2/gl2.h>


#include "Shader.h"
#include "Uniform.h"

class Simple2D : public ANAS::ShaderBase {

	private:
		
		ANAS::Uniform<float,1> uWidth;
		ANAS::Uniform<float,1> uHeight;
		ANAS::Uniform<float,1> uScrollx;
		ANAS::Uniform<float,1> uScrolly;
		
		float width;
		float height;
		float scroll[2];

	protected:
		
		void onInit(){
			
			glGetError();

			uWidth.Init( this->GetProgram(), "Width" );
			uHeight.Init( this->GetProgram(), "Height" );
			uScrollx.Init( this->GetProgram(), "Scrollx" );
			uScrolly.Init( this->GetProgram(), "Scrolly" );
			
			int error;
			if( ( error = glGetError()) != GL_NO_ERROR ){
				ANAS::Log::i("Simple2D", "Init error");
				switch(error){
					case GL_INVALID_ENUM:
						ANAS::Log::i("Simple2D", "GL_INVALID_ENUM");
						break;
					case GL_INVALID_VALUE:
						ANAS::Log::i("Simple2D", "GL_INVALID_VALUE");
						break;
					case GL_INVALID_OPERATION:
						ANAS::Log::i("Simple2D", "GL_INVALID_OPERATION");
						break;
					case GL_OUT_OF_MEMORY:
						ANAS::Log::i("Simple2D", "GL_OUT_OF_MEMORY");
						break;
				}
			}
		}

		void onSet(){

			//ANAS::Log::i("Simple2D", "Called onSet");

			uWidth.SetValue( width );
			uHeight.SetValue( height );

			uScrollx.SetValue( scroll[0] );
			uScrolly.SetValue( scroll[1] );

		}

	public:

		Simple2D( const char *vstring, const char *fstring)
			: ANAS::ShaderBase( vstring, fstring )
		{
			width = 1;
			height = 1;
			for(int i=0; i<2; i++) scroll[i] = 0;
		}

		void SetScreenSize( int w, int h ){
			width = (float)w;
			height = (float)h;
		}

		void SetScroll( int x, int y ){
			scroll[0] = (float)x;
			scroll[1] = (float)y;
		}
};


#endif /* __DEFINED_SHADER_SIMPLE2D__ */