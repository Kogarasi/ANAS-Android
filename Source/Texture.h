
#ifndef __DEFINED_ANAS_TEXTURE__
#define __DEFINED_ANAS_TEXTURE__


namespace ANAS {

	/**
	 * OpenGL用テクスチャ
	 * @author コガラシ
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
			 * 初期化関数
			 * @param data 画像データ列
			 * @param width 画像の幅
			 * @param height 画像の高さ
			 */
			 void Init( const unsigned char *data, int width, int height );

			 /**
			  * OpenGLへ設定する
			  * @param id テクスチャ番号何番に配置するか(デフォルトは0)
			  */
			 void Set(int id=0);

			 /**
			  * 拡大・縮小用のフィルタリング方法を指定
			  */
			 inline void SetFilter( int min, int mag ){
				 MinFilter = min;
				 MagFilter = mag;
			 }
	};
}

#endif /* __DEFINED_ANAS_TEXTURE__ */