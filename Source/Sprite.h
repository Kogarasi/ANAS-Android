
#ifndef __DEFINED_ANAS_SPRITE__
#define __DEFINED_ANAS_SPRITE__

#include "Shader.h"
#include "Uniform.h"

namespace ANAS {

	/**
	 * 2D表示をするためのスプライトクラス
	 * @author コガラシ
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
			 * 初期化関数
			 * @param pShader このスプライトで扱うシェーダー
			 */
			void Init( ANAS::ShaderBase * pShader);

			/*
			 * 描画関数
			 */
			void Render();

			
			/*
			 * UV設定用関数
			 * @param l 左側を指定
			 * @param t 上側を指定
			 * @param r 右側を指定
			 * @param b 下側を指定
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