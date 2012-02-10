
#include <unistd.h>
#include <math.h>

#include <boost/foreach.hpp>


#include "log.h"
#include "CustomSprite.h"

static const float vertex_list[] = {
    // X, Y, Z
    -0.5f, -0.5f, 0,
     0.5f, -0.5f, 0,
    -0.5f,  0.5f, 0,
     0.5f,  0.5f, 0
};

static const float uv_list[] = {
    // U, V
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f
};

static const unsigned int index_list[] = {
	0, 1, 2, 3
};

ANAS::CustomSprite::CustomSprite(){

	memcpy(UV, uv_list, sizeof(float)*8 );

	BOOST_FOREACH(float &v, Pos){ v = 0; }
	BOOST_FOREACH(float &v, Scale){ v = 1; }
	//Rotate = 0;
	BOOST_FOREACH(float &v, Color){ v = 1; }

	Time = 0;
}

ANAS::CustomSprite::~CustomSprite(){

	GLuint _buffer[] = { bufPos, bufTex, bufIdx };

	glDeleteBuffers( 3, _buffer );

}


void ANAS::CustomSprite::Init( ANAS::ShaderBase *pShader ){

	glGetError();

	int program = pShader->GetProgram();
	
	uPos.Init(program, "Pos");
	uScale.Init(program, "Scale");
	//uRot.Init(program, "Angle");
	uColor.Init(program, "Color");
	uTime.Init(program, "Time");

	
	aPos = glGetAttribLocation(program, "aPosition");
	aTex = glGetAttribLocation(program, "aTextureCoord");

	GLuint _buffer[3];
	glGenBuffers(3, _buffer);
	bufPos = _buffer[0];
	bufTex = _buffer[1];
	bufIdx = _buffer[2];

	BOOST_FOREACH(unsigned int &b, _buffer){
		ANAS::Log::i("GEN BUFFERS", (boost::format("ID:%1%")%b).str().c_str() );
	}

	// Pos
	glBindBuffer( GL_ARRAY_BUFFER, bufPos );
	glBufferData( GL_ARRAY_BUFFER, sizeof(float)*3*4, vertex_list, GL_STATIC_DRAW );
	
	// Tex
	glBindBuffer( GL_ARRAY_BUFFER, bufTex );
	glBufferData( GL_ARRAY_BUFFER, sizeof(float)*2*4, UV, GL_STATIC_DRAW );

	// Index
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, bufIdx );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*4, index_list, GL_STATIC_DRAW );

	glBindBuffer( GL_ARRAY_BUFFER, 0);
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0);

	ANAS::Log::i( "Attribute", (boost::format("Name:aPosition, No:%1%")%aPos).str().c_str() );
	ANAS::Log::i( "Attribute", (boost::format("Name:aTextureCoord, No:%1%")%aTex).str().c_str() );
	
	int error;
	if( ( error = glGetError() ) != GL_NO_ERROR ){

		ANAS::Log::i("INIT", (boost::format("%1%")%error).str().c_str() );

	}
}

void ANAS::CustomSprite::Render(){


	glGetError();

	{
		glBindBuffer( GL_ARRAY_BUFFER, bufPos );
		glVertexAttribPointer( aPos, 3, GL_FLOAT, GL_FALSE, 0, 0 );
		glEnableVertexAttribArray( aPos );
	}
	{
		glBindBuffer( GL_ARRAY_BUFFER, bufTex );
		glVertexAttribPointer( aTex, 2, GL_FLOAT, GL_FALSE, 0, 0 );
		glEnableVertexAttribArray( aTex );
	}


	// Set Uniform
	uPos.SetValue( Pos[0], Pos[1] );
	uScale.SetValue( Scale[0], Scale[1] );
	//uRot.SetValue( sinf( Rotate), cosf( Rotate ) );
	uColor.SetValue( Color[0], Color[1], Color[2], Color[3] );
	uTime.SetValue( Time );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, bufIdx );
	glDrawElements( GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer( GL_ARRAY_BUFFER, 0);
	
	int error;
	if( ( error = glGetError() ) != GL_NO_ERROR ){

		ANAS::Log::i("RENDER", (boost::format("%1%")%error).str().c_str() );

	}
}