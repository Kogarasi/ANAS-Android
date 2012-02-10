
#ifndef __DEFINED_SPLASH_SCENE__
#define __DEFINED_SPLASH_SCENE__

#include <boost/thread.hpp>

#include "SceneBase.h"

#include "AssetData.h"
#include "Simple2D.h"
#include "Sprite.h"
#include "Image.h"
#include "Texture.h"
#include "Time.h"
#include "Screen.h"

#include "GameScene.h"

namespace ANAS {

	/**
	 * スプラッシュスクリーン
	 * @author コガラシ
	 */
	class SplashScreenScene : public ANAS::SceneBase {
		private:

			Simple2D *pSimple2D;
			// Sprite
			ANAS::Sprite mTitleSprite;
			// Image
			ANAS::Image mTitleImage;
			// Texture
			ANAS::Texture mTitleTexture;

			ANAS::Time Time;

			int Counter;

		public:

			SplashScreenScene(){
				Counter = 360;
			}
			~SplashScreenScene(){}

			// virtual
			void Init(){

				// スクリーンの設定
				{
					ANAS::Screen::Adjust( 640, 480, ANAS::SO_FIXED );
					ANAS::Screen::ApplyToViewPort( pContainer->pGraphic );
					ANAS::Screen::ApplyToTouchScreen( pContainer->pInput );
				}

				// シェーダーの読み込み
				ANAS::ResourceHolder *pHolder = pResource->Get("SimpleShader");
				if( pHolder == NULL )
				{
					ANAS::Log::i("Scene Init", "Create Shader");

					ANAS::AssetData vString( pContainer->pActivity->assetManager );
					vString.Load( "simple2d.vsh" );
				
					ANAS::AssetData fString( pContainer->pActivity->assetManager );
					fString.Load( "simple2d.fsh" );

					pSimple2D = new Simple2D( vString.GetData(), fString.GetData() );
					pContainer->pGraphic->Add( new ANAS::AnyTasking( boost::bind( &ANAS::ShaderBase::Init, pSimple2D)) );

					// リソースマネージャへ登録
					pResource->Set( "SimpleShader", new ANAS::ResourceItem<Simple2D>(pSimple2D) );

				} else {
					ANAS::Log::i("Scene Init", "Get Exist Shader");

					// ホルダーから取得
					pSimple2D = ((ANAS::ResourceItem<Simple2D>*)pHolder)->Get();
				}

				// Title Logo
				{
					pContainer->pGraphic->Add( new ANAS::AnyTasking( boost::function<void()>(boost::bind( &ANAS::Sprite::Init, &mTitleSprite, pSimple2D) )) );
					mTitleSprite.Scale[0] = 640;
					mTitleSprite.Scale[1] = 480;
					mTitleSprite.Pos[0] = 320;
					mTitleSprite.Pos[1] = 240;
					mTitleSprite.SetUV( 0, 0, 640.f/1024.f, 480.f/1024.f );
					
					ANAS::AssetData aTitle( pContainer->pActivity->assetManager );
					aTitle.Load( "project_logo.png" );
					mTitleImage.Load<ANAS::IFT_PNG>( aTitle.GetData() );

					pContainer->pGraphic->Add( new ANAS::AnyTasking( boost::function<void()>(boost::bind( &ANAS::Texture::Init, &mTitleTexture, mTitleImage.Get(), 1024,1024) )) );
					
				}

				SetInitialized();
			}
			void Process(){
				
				// 入力処理
				ANAS::InputData State;
				do {
					State = pContainer->pInput->PopState();

					if( State.InputType == ANAS::IT_KEY ){
					} else if( State.InputType == ANAS::IT_MOTION ){
					}



				} while( State.KeyChar != -1 );

				if( Counter <= 0 ){

					//pNextScene = SceneBase::pStartScene;
					pNextScene = new Game::GameScene;
					SetSceneEnd();
				}

				mTitleSprite.Color[3] = sinf( Counter/360.f*3.14f );

				Counter--;
				
				{
					pContainer->pGraphic->Add( new ANAS::AnyTasking( boost::bind(&SplashScreenScene::Render, this) ) );
					pContainer->pGraphic->Swap( 0, 0, 0, 1);
				}

				Time.AdjustTime(1/60.0f);

			}
			void Render(){
				pSimple2D->SetScreenSize( ANAS::Screen::GameWidth(), ANAS::Screen::GameHeight() );
				pSimple2D->SetScroll(0, 0);
				pSimple2D->Set();

				mTitleTexture.Set();
				mTitleSprite.Render();
			}
	};
}


#endif /* __DEFINED_SPLASH_SCENE__ */
