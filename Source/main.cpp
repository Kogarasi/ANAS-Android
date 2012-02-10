
#include <unistd.h>
#include <pthread.h>

#include <android/configuration.h>
#include <android/native_activity.h>

#include <boost/function.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/thread.hpp>

#include "main.h"
#include "log.h"
#include "Activity.h"
#include "Input.h"
#include "Task.h"
#include "Graphic.h"
#include "SceneBase.h"

//#include "GameScene.h"
#include "SplashScreen.h"

extern "C" {
	// Andorid Native Activity Entry Point.
	void android_main(ANativeActivity*, void*, size_t);
}



void Main(BridgeParameter* arg){
	boost::scoped_ptr< BridgeParameter > param( arg );

	// Items
	ANAS::Input Input;
	ANAS::Graphic Graphic;

	// Set Configuration for Activity.
	ANAS::ActivityConfigration Configuration;
	{
		// Basic Param
		Configuration.pActivity = param->activity;
		Configuration.pSavedState = param->savedState;
		Configuration.SavedStateSize = param->savedStateSize;
	
		// Custom Param
		Configuration.pUserCallbacks = NULL;	// No Implement
	
		// Set to configuration class.
		Configuration.pInput = &Input;
		Configuration.pGraphic = &Graphic;
	}

	// Create Activity
	boost::scoped_ptr< ANAS::Activity > pActivity ( new ANAS::Activity( Configuration ) );

	// Push
	param->Notification();

	// Wait Init.
	Graphic.Wait();
	Input.Wait();


	// Scene
	ANAS::SceneContainer *pContainer = new ANAS::SceneContainer;
	{
		// Interfaces
		pContainer->pGraphic = &Graphic;
		pContainer->pInput = &Input;

		// Activity
		pContainer->pActivity = param->activity;

		// Startup Scene
		pContainer->pStartScene = new ANAS::SplashScreenScene;
		//pContainer->pStartScene = new Game::GameScene;
	}

	boost::scoped_ptr<ANAS::SceneManager> SceneManager ( new ANAS::SceneManager( pContainer ) );


	// I—¹‘Ò‚¿
	pContainer->NotifySignal.Wait();

	ANAS::Log::i( "System", "System Terminate" );

}

// Entry Point
void android_main(ANativeActivity* activity, void* savedState, size_t savedStateSize){

	ANAS::Log::i("System", "Build-Number :" __DATE__ "," __TIME__);

	// Create bridge paramaters
	BridgeParameter *param = new BridgeParameter(activity, savedState, savedStateSize);

	// Create main thread
	boost::thread MainThread(&Main, param);



	// Wait( blocking )
	param->Wait();

	return;
}
