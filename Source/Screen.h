

#ifndef __DEFINED_ANAS_SCREEN__
#define __DEFINED_ANAS_SCREEN__

#include <unistd.h>

#include <boost/function.hpp>
#include <boost/format.hpp>

#include "Input.h"
#include "Graphic.h"

namespace ANAS {

	enum ScreenOption {
		SO_DEFAULT,
		SO_FIXED,
		SO_SCALE,
		SO_FILL,

	};

	class Screen {

		private:
			// viewport
			static int vp_x;
			static int vp_y;
			static int vp_width;
			static int vp_height;

			// game screen
			static int gs_width;
			static int gs_height;

		public:

			static void Adjust( int w, int h, ANAS::ScreenOption Opt = ANAS::SO_DEFAULT ){

				switch( Opt ){
					case ANAS::SO_DEFAULT:

						vp_width = gs_width = ANAS::Graphic::Width;
						vp_height = gs_height = ANAS::Graphic::Height;

						vp_x = 0;
						vp_y = 0;

						break;

					case ANAS::SO_FIXED:

						// fixed game screen resultion.
						vp_width = gs_width = w;
						vp_height = gs_height =h;

						// set x,y pos.
						vp_x = (ANAS::Graphic::Width-w)/2;
						vp_y = (ANAS::Graphic::Height-h)/2;

						break;

					case ANAS::SO_SCALE:
						AdjustScaling( w, h, Opt );

						break;

					case ANAS::SO_FILL:
						vp_x = ANAS::Graphic::Width;
						vp_y = ANAS::Graphic::Height;

						gs_width = w;
						gs_height = h;
						break;
						
					default:
						break;
				}

			}

			// ビューポートへ設定を反映
			inline static void ApplyToViewPort( ANAS::Graphic *pGraphic ){

				pGraphic->Add( new ANAS::AnyTasking( boost::function<void()>( boost::bind(glViewport, vp_x, vp_y, vp_width, vp_height) ) ) );
			}
			// タッチ座標へ設定を反映
			inline static void ApplyToTouchScreen( ANAS::Input *pInput ){

				pInput->SetScreenOffset( vp_x, vp_y );
			}

			// ゲーム空間のサイズを取得
			inline static int GameWidth(){
				return gs_width;
			}
			inline static int GameHeight(){
				return gs_height;
			}

			// スケーリング用
			static void AdjustScaling( int w, int h, ANAS::ScreenOption Opt ){

				// 1.ゲームスクリーンのサイズを算出
				float Ratio = (float)w/(float)h;
				float revRatio = (float)h/(float)w;

				int fix_h = ANAS::Graphic::Height * Ratio;
				int min_resolution = ANAS::Graphic::Width < fix_h ? ANAS::Graphic::Width : fix_h;

				vp_width = gs_width = min_resolution;
				vp_height = gs_height = gs_width * revRatio;



				// 2.ビューポートのオフセットを算出
				vp_x = (ANAS::Graphic::Width - gs_width)/2;
				vp_y = (ANAS::Graphic::Height - gs_height)/2;

				boost::format resolution_fmt("GameScreen[x:%1%, y:%2%] ViewPortOffset[x:%3%, y:%4%]");
				ANAS::Log::i("Scaling Screen", (resolution_fmt%gs_width%gs_height%vp_x%vp_y).str().c_str() );

			}
	};
}

#endif /* __DEFINED_ANAS_SCREEN__ */