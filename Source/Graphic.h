
#ifndef __DEFINED_ANAS_GRAPHIC__
#define __DEFINED_ANAS_GRAPHIC__

#include <android/native_activity.h>
#include <android/native_window.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "Task.h"
#include "Signal.h"

namespace ANAS {

	/**
	 * グラフィック周りの担当をする
	 * OpenGLの処理はこのクラスへタスクを追加して行う
	 * TaskSchedulerクラスとSingalクラスを継承している
	 */
	class Graphic : public TaskScheduler, public Signal {

		private:

			
			ANativeWindow *pWindow;

			EGLDisplay eglDisplay;
			EGLSurface eglSurface;
			EGLContext eglContext;


		public:
			
			static int Width;
			static int Height;

			Graphic();
			~Graphic();
		
			/**
			 * OpenGLの初期化
			 * @param _window OpenGLを使いたいActivityのANativeWindow
			 */
			void Init(ANativeWindow *_window);

			/**
			 * OpenGLの破棄
			 */
			void Term();

			/**
			 * 画面の更新
			 * @param r glClearColorの赤
			 * @param g glClearColorの緑
			 * @param b glClearColorの青
			 * @param a glClearColorのα
			 */
			void Swap(float r, float g, float b, float a);

			/**
			 * 初期化処理のスレッド移譲用
			 */
			void InitTask();
			/**
			 * 破棄処理のスレッド移譲用
			 */
			void TermTask();
			/**
			 * 画面更新のスレッド移譲用
			 */
			void SwapTask( float r, float g, float b, float a);

	};
}

#endif /* __DEFINED_ANAS_GRAPHIC__ */