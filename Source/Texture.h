
#ifndef __DEFINED_ANAS_TEXTURE__
#define __DEFINED_ANAS_TEXTURE__


namespace ANAS {

	/**
	 * OpenGL�p�e�N�X�`��
	 * @author �R�K���V
	 */
	class Texture {
		private:
			int TextureID;

			int MinFilter;
			int MagFilter;
			int WrapTexture;

		public:

			Texture();
			~Texture();

			/**
			 * �������֐�
			 * @param data �摜�f�[�^��
			 * @param width �摜�̕�
			 * @param height �摜�̍���
			 */
			 void Init( const unsigned char *data, int width, int height );

			 /**
			  * OpenGL�֐ݒ肷��
			  * @param id �e�N�X�`���ԍ����Ԃɔz�u���邩(�f�t�H���g��0)
			  */
			 void Set(int id=0);

			 /**
			  * �g��E�k���p�̃t�B���^�����O���@���w��
			  */
			 inline void SetFilter( int min, int mag ){
				 MinFilter = min;
				 MagFilter = mag;
			 }
	};
}

#endif /* __DEFINED_ANAS_TEXTURE__ */