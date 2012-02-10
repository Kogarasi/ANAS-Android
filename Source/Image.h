
#ifndef __DEFINED_ANAS_IMAGE__
#define __DEFINED_ANAS_IMAGE__

#include <vector>
#include <png/png.h>

namespace ANAS {

	/**
	 * 画像タイプ指定用
	 * @author コガラシ
	 */
	enum ImageFileType {
		IFT_PNG,
	};

	/**
	 * 関数区別用テンプレート
	 * ImageFileTypeとあわせて使うことで読み込みに使用するLoad関数をコンパイル時に決定できる
	 * @author コガラシ
	 */
	template <ImageFileType T>
	struct Value {
		enum { v = T };
	};


	/**
	 * 画像読み込み用クラス
	 * 現在読めるのはPNGのみ
	 * @author コガラシ
	 */
	class Image {

		private:

			unsigned char *data;

			int Width;
			int Height;
			
			/**
			 * 画像読み込み関数(PNG)
			 * @param SourceBuffer PNGデータ列
			 * @param v テンプレート用
			 */
			void Load( const void *SourceBuffer, Value<IFT_PNG> v);
			

		public:

			Image();
			~Image();


			/**
			 * 画像読み込み関数
			 * テンプレートで対応する関数を呼び出し
			 * @param SourceBuffer 画像データ列
			 */
			template <ImageFileType T>
			void Load( const void *SourceBuffer ){
				Load( SourceBuffer, Value<T>() );
			}

			/**
			 * 読み込んだデータを取得
			 * @return データ列
			 */
			const unsigned char *Get(){
				return data;
			}
	};
}

#endif /* __DEFINED_ANAS_IMAGE__ */