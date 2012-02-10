
#include <boost/thread.hpp>

#include "SceneBase.h"
#include "log.h"



// �R���X�g���N�^
ANAS::SceneBase::SceneBase()
	:pNextScene(NULL), isSceneEnd(false), isInitialized(false){

}

// �f�X�g���N�^
ANAS::SceneBase::~SceneBase(){

	ANAS::Log::i("SceneBase", "Destructor");

}

// �R���X�g���N�^
ANAS::SceneManager::SceneManager(SceneContainer *pC)
	: pContainer(pC), pScene(pC->pStartScene){

		// �R���e�i�Z�b�g
		pScene->SetContainer(pC);

		// ���\�[�X�}�l�[�W���Z�b�g
		pScene->SetResourceManager( &ResourceManager );

		// �V�[���̏�����
		pScene->Init();

		// �V�[���̊J�n
		pThread = new Thread(this);
}

// �f�X�g���N�^
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

				// �R���e�i�Z�b�g
				pScene->SetContainer(pContainer);

				// ���\�[�X�}�l�[�W���Z�b�g
				pScene->SetResourceManager( &ResourceManager );

				// �V�[���̏�����
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
		
			// �����͉��B
			//pScene->Render();
		}
	}

	Timer.AdjustTime( 1/60.0f );

}