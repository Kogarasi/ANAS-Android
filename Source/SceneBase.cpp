
#include <boost/thread.hpp>

#include "SceneBase.h"
#include "log.h"



// コンストラクタ
ANAS::SceneBase::SceneBase()
	:pNextScene(NULL), isSceneEnd(false), isInitialized(false){

}

// デストラクタ
ANAS::SceneBase::~SceneBase(){

	ANAS::Log::i("SceneBase", "Destructor");

}

// コンストラクタ
ANAS::SceneManager::SceneManager(SceneContainer *pC)
	: pContainer(pC), pScene(pC->pStartScene){

		// コンテナセット
		pScene->SetContainer(pC);

		// リソースマネージャセット
		pScene->SetResourceManager( &ResourceManager );

		// シーンの初期化
		pScene->Init();

		// シーンの開始
		pThread = new Thread(this);
}

// デストラクタ
ANAS::SceneManager::~SceneManager(){

	if(pThread){
		delete pThread;
	}

	ANAS::Log::i("SCM", "Complete Destruct");
}

void ANAS::SceneManager::run(){
	//ANAS::Log::i("SCM", "running Scene Manager");


	if(pScene){

		if(pScene->CheckSceneEnd()){
			ANAS::Log::i("SCM", "Detected Scene End" );

			if( pScene->pNextScene ){

				ANAS::Log::i("SCM", "Step Scene");

				// Step
				SceneBase *_scene = pScene->pNextScene;
				delete pScene;
				pScene = _scene;

				// コンテナセット
				pScene->SetContainer(pContainer);

				// リソースマネージャセット
				pScene->SetResourceManager( &ResourceManager );

				// シーンの初期化
				pScene->Init();


			} else {
				// Exit.

				ANAS::Log::i( "SCM", "Scene Not Found. and Exit" );

				/*
				delete pScene;
				pScene = NULL;
				*/

				pContainer->NotifySignal.Notification();
			}
		} else if(pScene->isInitialized){
			pScene->Process();
		
			// こいつは仮。
			//pScene->Render();
		}
	}

	Timer.AdjustTime( 1/60.0f );

}