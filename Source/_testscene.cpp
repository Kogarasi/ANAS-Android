
#include "_testscene.h"


#include "AssetData.h"
#include "Task.h"

//#include "Sound.h"


test::testScene::testScene(){

}
test::testScene::~testScene(){
	pResource->Release( "SimpleShader" );
}

void test::testScene::Init(){
	theta = 0;

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

		pResource->Set( "SimpleShader", new ANAS::ResourceItem<Simple2D>(pSimple2D) );

	} else {
		ANAS::Log::i("Scene Init", "Get Exist Shader");

		pSimple2D = ((ANAS::ResourceItem<Simple2D>*)pHolder)->Get();
	}


	// スプライトの初期化
	{
	
		ANAS::Task *_t = new ANAS::AnyTasking( boost::function<void()>(boost::bind( &ANAS::Sprite::Init, &mTestSprite, pSimple2D )) );
		pContainer->pGraphic->Add(_t);

		mTestSprite.Pos[0] = 300;
		mTestSprite.Pos[1] = 300;
		mTestSprite.Scale[0] = 300;
		mTestSprite.Scale[1] = 300;
	}
	
	// テクスチャの初期化
	
	{
		
		ANAS::AssetData aImage( pContainer->pActivity->assetManager );
		aImage.Load( "android_logo.png" );
		AndroidImage.Load<ANAS::IFT_PNG>( aImage.GetData() );

		pContainer->pGraphic->Add( new ANAS::AnyTasking( boost::function<void()>(boost::bind( &ANAS::Texture::Init, &mTestTexture, AndroidImage.Get(), 128, 128) )) );
		
	}


	
	/*
	ANAS::Sound *pSound = new ANAS::Sound();
	ANAS::AssetData TestSound( pContainer->pActivity->assetManager );
	int dst[3];
	TestSound.GetFileDescriptor( "data.mp3", &dst[0], &dst[1], &dst[2] );

	ANAS::Log::i( "ASSET",(boost::format("%1%:%2%:%3%")%dst[0]%dst[1]%dst[2]).str().c_str() );

	pSound->Load( dst[0], dst[1], dst[2] );
	*/

	// set flag initialized.
	SetInitialized();
}

void test::testScene::Process(){
				
	ANAS::InputData State;
	do {
		State = pContainer->pInput->PopState();

		if( State.InputType == ANAS::IT_KEY ){
			if( State.KeyChar == ANAS::IK_BACK ){

				ANAS::Log::i("test Scene", "Detect Back Key");

				GameExit();
				//pNextScene = new test::testScene;
				//SetSceneEnd();

				break;
			}
		} else if( State.InputType == ANAS::IT_MOTION ){
			mTestSprite.Pos[0] = State.Pos.x;
			mTestSprite.Pos[1] = State.Pos.y;
		}


	} while( State.KeyChar != -1 );

	//if( pContainer->pGraphic->CheckSleep() )
	{
		theta += 0.02f;

		
		pContainer->pGraphic->Add( new ANAS::AnyTasking( boost::bind(&testScene::Render, this) ) );
		pContainer->pGraphic->Swap( fabs(sin(theta)), fabs(cos(theta)), 0, 1);
	}

}

void test::testScene::Render(){

	pSimple2D->SetScreenSize( ANAS::Graphic::Width, ANAS::Graphic::Height );
	pSimple2D->SetScroll(0, 0);
	pSimple2D->Set();

	mTestTexture.Set();
	mTestSprite.Render();
}