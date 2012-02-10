

#include "log.h"
#include "Activity.h"

#include "Image.h"

// ==== コンストラクタ
ANAS::Activity::Activity( ANAS::ActivityConfigration &_conf ):
pActivity( _conf.pActivity ), pSavedState( _conf.pSavedState ), SavedStateSize( _conf.SavedStateSize ),
	pCallBacks( _conf.pUserCallbacks ), pInputInterface( _conf.pInput ), pGraphicInterface( _conf.pGraphic )
{
	Log::i("Activity Constructor","Start Construction" );

	// Destroy Sync.
	DestroyFuture = DestroyPromise.get_future();

	
	// Config
	pConfig = AConfiguration_new();
	if(pConfig){
		AConfiguration_fromAssetManager(pConfig, pActivity->assetManager);
	}

	// Test Code.
	
	/*
	const char* asset_name = "android_logo.png";
	AAsset *asset = AAssetManager_open(pActivity->assetManager, asset_name, AASSET_MODE_STREAMING);
	if(asset){
		int Asset_size = AAsset_getLength(asset);
		const void *Asset_ptr = AAsset_getBuffer(asset);


		boost::format asset_format("FILE: %1%, SIZE: %2%");
		Log::e("Asset Test", (asset_format % asset_name % Asset_size).str().c_str() );
		
		
		Image _test_img;
		_test_img.Load<IFT_PNG>( Asset_ptr );

		AAsset_close( asset );
	}
	*/
	


	// CallBacks
	SetCallBacks(pActivity->callbacks);

	Log::i("Activity Constructor", "End Construction");
}

// ==== デストラクタ
ANAS::Activity::~Activity()
{

	Log::i("Activity Destructor", "Start Destruction");

	// アクティビティの終了宣言
	ANativeActivity_finish(pActivity);

	AConfiguration_delete(pConfig);
	
	// Wait "onDestroy" Callback is called.
	DestroyFuture.get();

	Log::i("Activity Destructor", "End Destruction");
}


// make_c_function
template <typename UUID, typename F> struct activity_function {
		
		
	static void called(ANativeActivity *activity){

		DestFunction(activity);
	}
	static void called(ANativeActivity* activity, int focused){

		DestFunction(activity, focused);

	}
	static void called(ANativeActivity* activity, ANativeWindow *window){

		DestFunction(activity, window);

	}
	static void called(ANativeActivity* activity, AInputQueue* queue){

		DestFunction(activity, queue);

	}

	static F DestFunction;
};
template <typename UUID, typename F> F activity_function<UUID,F>::DestFunction;

template <typename UUID, typename Function, typename F > Function make_activity_function(F func) {
		
	activity_function<UUID, F>::DestFunction = func;

	return &activity_function<UUID, F>::called;

}

// ==== コールバックの設定
void ANAS::Activity::SetCallBacks(ANativeActivityCallbacks *callbacks){

	callbacks->onDestroy = make_activity_function<struct UUID_Destory, void(*)(ANativeActivity*)>(
		boost::function<void(ANativeActivity*)>( boost::bind(&Activity::onDestroy, this, _1))
		);
	callbacks->onStart = make_activity_function<struct UUID_Start, void(*)(ANativeActivity*)>(
		boost::function<void(ANativeActivity*)>( boost::bind(&Activity::onStart, this, _1))
		);
	callbacks->onResume = make_activity_function<struct UUID_Resume, void(*)(ANativeActivity*)>(
		boost::function<void(ANativeActivity*)>( boost::bind(&Activity::onResume, this, _1))
		);
				
	callbacks->onPause = make_activity_function<struct UUID_Pause, void(*)(ANativeActivity*)>(
		boost::function<void(ANativeActivity*)>( boost::bind(&Activity::onPause, this, _1))
		);
				
	callbacks->onStop = make_activity_function<struct UUID_Stop, void(*)(ANativeActivity*)>(
		boost::function<void(ANativeActivity*)>( boost::bind(&Activity::onStop, this, _1))
		);

	callbacks->onConfigurationChanged = make_activity_function<struct UUID_ConfigurationChanged, void(*)(ANativeActivity*)>(
		boost::function<void(ANativeActivity*)>( boost::bind(&Activity::onConfigurationChanged, this, _1))
		);


	callbacks->onLowMemory = make_activity_function<struct UUID_LowMemory, void(*)(ANativeActivity*)>(
		boost::function<void(ANativeActivity*)>( boost::bind(&Activity::onLowMemory, this, _1))
		);


	callbacks->onWindowFocusChanged = make_activity_function<struct UUID_WindowFocusChanged, void(*)(ANativeActivity*, int)>(
		boost::function<void(ANativeActivity*,int)>( boost::bind(&Activity::onWindowFocusChanged, this, _1, _2))
		);

	// Window
	callbacks->onNativeWindowCreated = make_activity_function<struct UUID_NativeWindowCreated, void(*)(ANativeActivity*, ANativeWindow*)>(
		boost::function<void(ANativeActivity*, ANativeWindow*)>( boost::bind(&Activity::onNativeWindowCreated, this, _1, _2))
		);

	callbacks->onNativeWindowDestroyed = make_activity_function<struct UUID_NativeWindowDestroyed, void(*)(ANativeActivity*, ANativeWindow*)>(
		boost::function<void(ANativeActivity*, ANativeWindow*)>( boost::bind(&Activity::onNativeWindowDestroyed, this, _1, _2))
		);


	// Input
	
	callbacks->onInputQueueCreated = make_activity_function<struct UUID_InputQueueCreated, void(*)(ANativeActivity*, AInputQueue*)>(
		boost::function<void(ANativeActivity*, AInputQueue*)>( boost::bind(&Activity::onInputQueueCreated, this, _1, _2))
		);

	callbacks->onInputQueueDestroyed = make_activity_function<struct UUID_InputQueueDestroyed, void(*)(ANativeActivity*, AInputQueue*)>(
		boost::function<void(ANativeActivity*, AInputQueue*)>( boost::bind(&Activity::onInputQueueDestroyed, this, _1, _2))
		);
		
}



void ANAS::Activity::onConfigurationChanged(ANativeActivity* activity){
	Log::i("Activity CallBacks", "Called onConfigurationChanged");
}
void ANAS::Activity::onDestroy(ANativeActivity* activity){
	Log::i("Activity CallBacks", "Called onDestroy");

	DestroyPromise.set_value();
}
void ANAS::Activity::onStart(ANativeActivity* activity){
	Log::i("Activity CallBacks", "Called onStart");
}
void ANAS::Activity::onResume(ANativeActivity* activity){
	Log::i("Activity CallBacks", "Called onResume");
}
void ANAS::Activity::onPause(ANativeActivity* activity){
	Log::i("Activity CallBacks", "Called onPause");
}
void ANAS::Activity::onStop(ANativeActivity* activity){
	Log::i("Activity CallBacks", "Called onStop");
}
void ANAS::Activity::onLowMemory(ANativeActivity* activity){
	Log::i("Activity CallBacks", "Called onLowMemory");
}

			
void ANAS::Activity::onWindowFocusChanged(ANativeActivity* activity, int focused){
	Log::i("Activity CallBacks", "Called onWindowFocusChanged");
}

void ANAS::Activity::onSaveInstanceState(ANativeActivity* activity, size_t* outLen){
	Log::i("Activity CallBacks", "Called onSaveInstanceState");
}
void ANAS::Activity::onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window){
	Log::i("Activity CallBacks", "Called onNativeWindowCreated");

	if( pGraphicInterface ){
		pGraphicInterface->Init( window );
	}

}
void ANAS::Activity::onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window){
	Log::i("Activity CallBacks", "Called onNativeWindowDestroyed");

	
	if( pGraphicInterface ){
		pGraphicInterface->Term();
	}
	
}
void ANAS::Activity::onInputQueueCreated(ANativeActivity* activity, AInputQueue* queue){
	Log::i("Activity CallBacks", "Called onInputQueueCreated");

	if( pInputInterface ){
		pInputInterface->Init( queue );
	}
	
}
void ANAS::Activity::onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue){
	Log::i("Activity CallBacks", "Called onInputQueueDestroyed");

	if( pInputInterface ){
		pInputInterface->Term();
	}

}