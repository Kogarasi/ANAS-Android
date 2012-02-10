
#include <GLES2/gl2.h>
#include "log.h"

#include "Texture.h"

// �R���X�g���N�^
ANAS::Texture::Texture(){
	MinFilter = GL_NEAREST;
	MagFilter = GL_LINEAR;
	WrapTexture = GL_REPEAT;
}

// �f�X�g���N�^
ANAS::Texture::~Texture(){
}

// ������
void ANAS::Texture::Init( const unsigned char *data, int width, int height ){

	ANAS::Log::i("Texture", "Start Load");

	GLuint buffer;
	glGenTextures(1, &buffer);
	TextureID = buffer;

	glBindTexture( GL_TEXTURE_2D, TextureID);

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );

	glBindTexture( GL_TEXTURE_2D, 0);
}

// �e�N�X�`���̎g�p
void ANAS::Texture::Set(int id){

glActiveTexture( GL_TEXTURE0 + id );
glBindTexture( GL_TEXTURE_2D, TextureID );

glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MinFilter);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MagFilter);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapTexture);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapTexture);
}