
#include <unistd.h>

#include <boost/scoped_array.hpp>
#include <boost/function.hpp>
#include <boost/format.hpp>

#include "Image.h"
#include "log.h"

// PNG読み込み用コールバック関数
void PngReadFunc(png_struct *pPng, png_bytep buf, png_size_t size){

    unsigned char **Buffer = (unsigned char**)png_get_io_ptr(pPng);

    memcpy(buf, *Buffer, size);
    *Buffer += size;
 }

// コンストラクタ
ANAS::Image::Image()
:data(NULL)
{
}
// デストラクタ
ANAS::Image::~Image(){

	if(data){
		delete[] data;
	}
}

// PNG読み込み
void ANAS::Image::Load( const void *Buffer, Value<IFT_PNG>){

	ANAS::Log::i("PNG LOAD", "Start Loading");

	// png
	png_structp png_p;
	png_infop inf_p;
		
	// png 初期化
	{
		png_p = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0,0,0 );
		inf_p = png_create_info_struct( png_p );
		
		if( setjmp( png_jmpbuf(png_p) ) ){
			// error
			png_destroy_read_struct( &png_p, &inf_p, NULL );

			return;
		}

		// コールバックを設定
		png_set_read_fn(png_p, (png_voidp)&Buffer, (png_rw_ptr)PngReadFunc );

	}

	// 画像情報を取得
	png_uint_32 w, h;
	int BitDepth, ColorType;
	{
		png_read_info(png_p, inf_p);

		png_get_IHDR(png_p, inf_p, &w, &h, &BitDepth, &ColorType, NULL, NULL, NULL);

		// 色深度チェック
		if(BitDepth==16){
			png_set_strip_16(png_p);
		}
		if( ColorType & PNG_COLOR_MASK_ALPHA ){
			//png_set_strip_alpha( png_p );
		} else {
			//png_set_filter( png_p, 255, 1 );
		}

		Width = w;
		Height = h;

		ANAS::Log::i("Image", (boost::format("W:%1%, H:%2%, COLOR:%3%, BITDEPTH:%4%")%Width%Height%ColorType%BitDepth).str().c_str() );
	}

	// 設定を反映
	png_read_update_info(png_p, inf_p);


	// データを読み込み
	{
		png_size_t RowSize = png_get_rowbytes( png_p, inf_p );
		int channels = (int)png_get_channels( png_p, inf_p );

		data = new unsigned char[ RowSize * Height ];
		boost::scoped_array<png_bytep> row_p( new png_bytep[ Height ] );
	
		// 行開始位置のポインタをセット
		for(int i=0; i<Height; i++){
			row_p[i] = data + (i*RowSize);
		}
		//png_set_bgr( png_p );
		png_read_image( png_p, row_p.get() );
	}

	// 終了
	png_read_end(png_p, NULL );

	
	ANAS::Log::i("PNG LOAD", "Complete Loading");
}