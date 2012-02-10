
#ifndef __DEFINED_ANAS_IMAGE__
#define __DEFINED_ANAS_IMAGE__

#include <vector>
#include <png/png.h>

namespace ANAS {

	/**
	 * �摜�^�C�v�w��p
	 * @author �R�K���V
	 */
	enum ImageFileType {
		IFT_PNG,
	};

	/**
	 * �֐���ʗp�e���v���[�g
	 * ImageFileType�Ƃ��킹�Ďg�����Ƃœǂݍ��݂Ɏg�p����Load�֐����R���p�C�����Ɍ���ł���
	 * @author �R�K���V
	 */
	template <ImageFileType T>
	struct Value {
		enum { v = T };
	};


	/**
	 * �摜�ǂݍ��ݗp�N���X
	 * ���ݓǂ߂�̂�PNG�̂�
	 * @author �R�K���V
	 */
	class Image {

		private:

			unsigned char *data;

			int Width;
			int Height;
			
			/**
			 * �摜�ǂݍ��݊֐�(PNG)
			 * @param SourceBuffer PNG�f�[�^��
			 * @param v �e���v���[�g�p
			 */
			void Load( const void *SourceBuffer, Value<IFT_PNG> v);
			

		public:

			Image();
			~Image();


			/**
			 * �摜�ǂݍ��݊֐�
			 * �e���v���[�g�őΉ�����֐����Ăяo��
			 * @param SourceBuffer �摜�f�[�^��
			 */
			template <ImageFileType T>
			void Load( const void *SourceBuffer ){
				Load( SourceBuffer, Value<T>() );
			}

			/**
			 * �ǂݍ��񂾃f�[�^���擾
			 * @return �f�[�^��
			 */
			const unsigned char *Get(){
				return data;
			}
	};
}

#endif /* __DEFINED_ANAS_IMAGE__ */