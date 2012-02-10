

#ifndef __DEFINED_ANAS_ACTIVITY__
#define __DEFINED_ANAS_ACTIVITY__


#include <android/native_activity.h>
#include <android/configuration.h>
#include <android/looper.h>
#include <android/sensor.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/format.hpp>
#include <boost/thread.hpp>

#include "Input.h"
#include "Graphic.h"

namespace ANAS {

	/**
	 * アクティビティのコールバック関数群
	 * @author コガラシ
	 */
	class ActivityCallbacks {
		public:
			virtual void onConfigurationChanged(ANativeActivity*) = 0;
			virtual void onDestroy(ANativeActivity*) = 0;
			virtual void onStart(ANativeActivity*) = 0;
			virtual void onResume(ANativeActivity*) = 0;
			virtual void onPause(ANativeActivity*) = 0;
			virtual void onStop(ANativeActivity*) = 0;
			virtual void onLowMemory(ANativeActivity*) = 0;

			
			virtual void onWindowFocusChanged(ANativeActivity*, int focused) = 0;

			virtual void onSaveInstanceState(ANativeActivity*, size_t* outLen) = 0;
			
			virtual void onNativeWindowCreated(ANativeActivity*, ANativeWindow*) = 0;
			virtual void onNativeWindowDestroyed(ANativeActivity*, ANativeWindow*) = 0;

			virtual void onInputQueueCreated(ANativeActivity*, AInputQueue*) = 0;
			virtual void onInputQueueDestroyed(ANativeActivity*, AInputQueue*) = 0;
	};

	/**
	 * アクティビティを初期化するためのデータ群
	 * @author コガラシ
	 */
	class ActivityConfigration {

		public:

			ANativeActivity		*pActivity;

			void				*pSavedState;
			int					SavedStateSize;

			ActivityCallbacks	*pUserCallbacks;
			ANAS::Input			*pInput;
			ANAS::Graphic		*pGraphic;

			ActivityConfigration(){
				pActivity = NULL;
				pSavedState = NULL;
				SavedStateSize = 0;

				pUserCallbacks = NULL;
				pInput = NULL;

			}
	};

	/**
	 * アクティビティの処理をするためのクラス
	 * @author コガラシ
	 */
	class Activity {

		private:
			ActivityCallbacks	*pCallBacks;

			ANAS::Input			*pInputInterface;
			ANAS::Graphic		*pGraphicInterface;

			boost::unique_future<void>	DestroyFuture;
			boost::promise<void>		DestroyPromise;

			// System
			ANativeActivity		*pActivity;
			void				*pSavedState;
			int					SavedStateSize;
			AConfiguration		*pConfig;

			Activity();


		public:
			Activity(ActivityConfigration &Configration);

			~Activity();

			/**
			 * コールバック関数を設定
			 */
			void SetCallBacks(ANativeActivityCallbacks * callbacks);



			// Behavior
			void onConfigurationChanged(ANativeActivity*);
			void onDestroy(ANativeActivity*);
			void onStart(ANativeActivity*);
			void onResume(ANativeActivity*);
			void onPause(ANativeActivity*);
			void onStop(ANativeActivity*);
			void onLowMemory(ANativeActivity*);
			void onWindowFocusChanged(ANativeActivity*, int);
			void onSaveInstanceState(ANativeActivity*, size_t* );
			void onNativeWindowCreated(ANativeActivity*, ANativeWindow*);
			void onNativeWindowDestroyed(ANativeActivity*, ANativeWindow*);
			void onInputQueueCreated(ANativeActivity*, AInputQueue*);
			void onInputQueueDestroyed(ANativeActivity*, AInputQueue*);
	};
}


#endif /* __DEFINED_ANAS_ACTIVITY__ */
