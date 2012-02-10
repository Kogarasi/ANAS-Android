#include <unistd.h>
#include <cstdlib>

#include <boost/function.hpp>
#include <boost/foreach.hpp>

#include "AssetData.h"
#include "Screen.h"

#include "GameScene.h"





Game::GameScene::GameScene(){
	srand( time(NULL));
}
Game::GameScene::~GameScene(){
	pResource->Release( "SimpleShader" );

	BOOST_FOREACH( BombData* v, BombList ){
		delete v;
	}

	BOOST_FOREACH( Enemy::EnemyBase* v, EnemyList ){
		delete v;
	}
}

void Game::GameScene::Init(){

	// スクリーンの設定
	{
		ANAS::Screen::Adjust( 0, 0, ANAS::SO_DEFAULT );
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


	// スプライトの初期化
	{

		// Tile
		pContainer->pGraphic->Add( new ANAS::AnyTasking( boost::function<void()>(boost::bind( &ANAS::Sprite::Init, &mTileSprite, pSimple2D) )) );
		mTileSprite.Scale[0] = TileSize;
		mTileSprite.Scale[1] = TileSize;

		// Bomb
		pContainer->pGraphic->Add( new ANAS::AnyTasking( boost::function<void()>(boost::bind( &ANAS::Sprite::Init, &mBombSprite, pSimple2D) )) );
		mBombSprite.Scale[0] = TileSize;
		mBombSprite.Scale[1] = TileSize;

		// Shadow
		pContainer->pGraphic->Add( new ANAS::AnyTasking( boost::function<void()>(boost::bind( &ANAS::Sprite::Init, &mShadowSprite, pSimple2D) )) );
		mShadowSprite.Scale[0] = TileSize*2;
		mShadowSprite.Scale[1] = TileSize*2;

		// BombLine
		pContainer->pGraphic->Add( new ANAS::AnyTasking( boost::function<void()>(boost::bind( &ANAS::Sprite::Init, &mBombLineSprite, pSimple2D) )) );
		mBombLineSprite.Scale[0] = 256;
		mBombLineSprite.Scale[1] = 256;

		// Enemy
		pContainer->pGraphic->Add( new ANAS::AnyTasking( boost::function<void()>(boost::bind( &ANAS::Sprite::Init, &mEnemySprite, pSimple2D) )) );
		mEnemySprite.Scale[0] = Enemy::ImageSize;
		mEnemySprite.Scale[1] = Enemy::ImageSize;
	}
	
	// テクスチャの初期化
	{
				
		// Tile
		ANAS::AssetData aTile( pContainer->pActivity->assetManager );
		aTile.Load( "tile.png" );
		mTileImage.Load<ANAS::IFT_PNG>( aTile.GetData() );

		pContainer->pGraphic->Add( new ANAS::AnyTasking( boost::function<void()>(boost::bind( &ANAS::Texture::Init, &mTileTexture, mTileImage.Get(), 2,2) )) );
		mTileTexture.SetFilter(GL_NEAREST, GL_NEAREST);

		// Bomb
		ANAS::AssetData aBomb( pContainer->pActivity->assetManager );
		aBomb.Load( "bomb.png" );
		mBombImage.Load<ANAS::IFT_PNG>( aBomb.GetData() );

		pContainer->pGraphic->Add( new ANAS::AnyTasking( boost::function<void()>(boost::bind( &ANAS::Texture::Init, &mBombTexture, mBombImage.Get(), 128, 128) )) );

		// Shadow
		ANAS::AssetData aShadow( pContainer->pActivity->assetManager );
		aShadow.Load( "shadow.png" );
		mShadowImage.Load<ANAS::IFT_PNG>( aShadow.GetData() );

		pContainer->pGraphic->Add( new ANAS::AnyTasking( boost::function<void()>(boost::bind( &ANAS::Texture::Init, &mShadowTexture, mShadowImage.Get(), 16, 16) )) );

		// BombLine
		ANAS::AssetData aBombLine( pContainer->pActivity->assetManager );
		aBombLine.Load( "line.png" );
		mBombLineImage.Load<ANAS::IFT_PNG>( aBombLine.GetData() );

		pContainer->pGraphic->Add( new ANAS::AnyTasking( boost::function<void()>(boost::bind( &ANAS::Texture::Init, &mBombLineTexture, mBombLineImage.Get(), 256, 256) )) );


		for(int i=0; i<1; i++){
			ANAS::AssetData aEnemy( pContainer->pActivity->assetManager );
			aEnemy.Load( Enemy::ImageName[i] );

			mEnemyImage[i].Load<ANAS::IFT_PNG>( aEnemy.GetData() );

			pContainer->pGraphic->Add( new ANAS::AnyTasking( boost::function<void()>(boost::bind( &ANAS::Texture::Init, &mEnemyTexture[i], mEnemyImage[i].Get(), 256, 256) )) );
		}
	}



	
	/*
	ANAS::Sound *pSound = new ANAS::Sound();
	ANAS::AssetData TestSound( pContainer->pActivity->assetManager );
	int dst[3];
	TestSound.GetFileDescriptor( "data.mp3", &dst[0], &dst[1], &dst[2] );

	ANAS::Log::i( "ASSET",(boost::format("%1%:%2%:%3%")%dst[0]%dst[1]%dst[2]).str().c_str() );

	pSound->Load( dst[0], dst[1], dst[2] );
	*/

	AttackIntervalCounter = AttackInterval;

	// set flag initialized.
	SetInitialized();
}

void Game::GameScene::Process(){

	// 入力処理
	ANAS::InputData State;
	do {
		State = pContainer->pInput->PopState();

		if( State.InputType == ANAS::IT_KEY ){
			if( State.KeyChar == ANAS::IK_BACK ){

				ANAS::Log::i("Game Scene", "Detect Back Key");

				GameExit();
				//pNextScene = new test::testScene;
				//SetSceneEnd();

				break;
			}
		} else if( State.InputType == ANAS::IT_MOTION ){
			//mTestSprite.Pos[0] = State.x;
			//mTestSprite.Pos[1] = State.y;

			ANAS::Log::i("Input State", "Peek Motion");
			ANAS::Log::i("Input State", (boost::format("Type:%1%, x:%2%, y:%3%, C:%4%")%State.ActionType%State.Pos.x%State.Pos.y%AttackIntervalCounter).str().c_str());

			if(State.ActionType == AMOTION_EVENT_ACTION_DOWN && (AttackIntervalCounter <= 0) ){

				// Lock
				boost::mutex::scoped_lock Lock(Mutex);

				BombData *pdata = new BombData;
				pdata->x = State.Pos.x;
				pdata->y = State.Pos.y;
				pdata->life = BombLife;

				BombList.push_back(pdata);

				AttackIntervalCounter = AttackInterval;
			}
		}



	} while( State.KeyChar != -1 );

	//mTestSprite.Time += 0.01f;
	{
		// Lock
		boost::mutex::scoped_lock Lock(Mutex);

		std::vector<BombData*>::iterator Ite = BombList.begin();
		while( Ite != BombList.end() ){

			(*Ite)->life--;

			// Life*2
			(*Ite)->x+= (0.5f*TileSize)/(BombLife*2);
			(*Ite)->y+= (0.5f*TileSize)/(BombLife*2);
			
			// ライフの切れたのを消去
			if( (*Ite)->life <= 0){


				bool isHit= false;

				// 当たり判定
				BOOST_FOREACH( Enemy::EnemyBase *v, EnemyList ){
					isHit |= v->HitCheck( (*Ite)->x, (*Ite)->y, 64, 1 );
				}

				// 当たっていれば爆発
				if( isHit ){
					Effect::BombLine _temp;
					_temp.x = (*Ite)->x;
					_temp.y = (*Ite)->y;
					_temp.life = 64;
					_temp.theta = 0;
					_temp.pSprite = &mBombLineSprite;

					BombLineEffect.Create( _temp );
				}


				// 消去
				delete *Ite;
				Ite = BombList.erase( Ite );
				continue;
			}

			Ite++;
		}
	}

	if(rand()%120 == 0){
		float x = rand()%ANAS::Screen::GameWidth();
		float y = rand()%ANAS::Screen::GameHeight();

		Enemy::EnemyBase *pEnemy = new Enemy::Soldier(x,y);
		pEnemy->pSprite = &mEnemySprite;
		pEnemy->pTexture = &mEnemyTexture[0];

		EnemyList.push_back( pEnemy );
	}

	{
		std::list<Enemy::EnemyBase*>::iterator Ite = EnemyList.begin();
		while( Ite != EnemyList.end() ){

			if( (*Ite)->isDied ){
				delete *Ite;
				Ite = EnemyList.erase( Ite );
				continue;
			} else {
				(*Ite)->Action();
			}

			Ite++;
		}
	}
	/*
	BOOST_FOREACH( Enemy::EnemyBase *v, EnemyList ){
		v->Action();
	}
	*/

	// エフェクトの動作
	BombLineEffect.Move();

	//if( pContainer->pGraphic->CheckSleep() )
	{

		
		pContainer->pGraphic->Add( new ANAS::AnyTasking( boost::bind(&GameScene::Render, this) ) );
		pContainer->pGraphic->Swap( 0, 0, 0, 1);
	}

	AttackIntervalCounter--;
	if(AttackIntervalCounter <= 0){
		AttackIntervalCounter = 0;
	}
	Time.AdjustTime(1/60.0f);

}

void Game::GameScene::Render(){

	pSimple2D->SetScreenSize( ANAS::Screen::GameWidth(), ANAS::Screen::GameHeight() );
	pSimple2D->SetScroll(0, 0);
	pSimple2D->Set();

	// Tile
	mTileTexture.Set();
	for(int i=0; i<MapX; i++){

		mTileSprite.Pos[0] = TileSize * ( i + 0.5f );

		for(int j=0; j<MapY; j++){
			mTileSprite.Pos[1] = TileSize * ( j + 0.5f );

			mTileSprite.Render();
		}
	}

	// Enemy
	BOOST_FOREACH( Enemy::EnemyBase *v, EnemyList ){
		v->Render();
	}
	
	mBombLineTexture.Set();
	BombLineEffect.Render();

	
	// Bomb
	{
		// Lock
		boost::mutex::scoped_lock Lock(Mutex);

		BOOST_FOREACH( BombData *&v, BombList ){
			float perLife = (v->life/(float)BombLife);

			mBombSprite.Pos[0] = v->x;
			mBombSprite.Pos[1] = v->y;
			mBombSprite.Scale[0] = TileSize * ( 1 + perLife );
			mBombSprite.Scale[1] = TileSize * ( 1 + perLife );

			float offset = perLife * TileSize*0.25f;
			mShadowSprite.Pos[0] = v->x + offset;
			mShadowSprite.Pos[1] = v->y + offset;
			mShadowSprite.Scale[0] = (1-perLife) * TileSize;
			mShadowSprite.Scale[1] = (1-perLife) * TileSize;

			mShadowTexture.Set();
			mShadowSprite.Render();

			
			mBombTexture.Set();
			mBombSprite.Render();
		}

	}
	

}