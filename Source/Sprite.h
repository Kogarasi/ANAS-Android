
#ifndef __DEFINED_ANAS_SPRITE__
#define __DEFINED_ANAS_SPRITE__

#include "Shader.h"
#include "Uniform.h"

namespace ANAS {

	/**
	 * 2D�\�������邽�߂̃X�v���C�g�N���X
	 * @author �R�K���V
	 */
	class Sprite {
		private:


			ANAS::Uniform<float,2> uPos;
			ANAS::Uniform<float,2> uScale;
			ANAS::Uniform<float,2> uRot;
			ANAS::Uniform<float,4> uColor;

			int aPos;
			int aTex;

			int bufPos;
			int bufTex;
			int bufIdx;

			float UV[8];

		public:

			float Pos[2];
			float Scale[2];
			float Rotate;
			float Color[4];

			Sprite();
			~Sprite();

			/*
			 * �������֐�
			 * @param pShader ���̃X�v���C�g�ň����V�F�[�_�[
			 */
			void Init( ANAS::ShaderBase * pShader);

			/*
			 * �`��֐�
			 */
			void Render();

			
			/*
			 * UV�ݒ�p�֐�
			 * @param l �������w��
			 * @param t �㑤���w��
			 * @param r �E�����w��
			 * @param b �������w��
			 */
			inline void SetUV( float l , float t, float r, float b ){
				UV[0] = l;
				UV[4] = l;

				UV[1] = t;
				UV[3] = t;

				UV[2] = r;
				UV[6] = r;

				UV[5] = b;
				UV[7] = b;

			}
	};
}

#endif /* __DEFINED_ANAS_SPRITE__ */