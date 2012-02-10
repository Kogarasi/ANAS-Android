
#include <android/native_activity.h>
#include <android/native_window.h>

#include <boost/function.hpp>
#include <boost/format.hpp>


#include "log.h"
#include "Graphic.h"


int ANAS::Graphic::Width = -1;
int ANAS::Graphic::Height = -1;

// コンストラクタ
ANAS::Graphic::Graphic(){}

// デストラクタ
ANAS::Graphic::~Graphic(){}

// 初期化（呼び出し用）
void ANAS::Graphic::Init( ANativeWindow *_window ){

	pWindow = _window;

	Add(new AnyTasking( boost::bind(&ANAS::Graphic::InitTask, this) ) );


	Swap(0,0,1,1);

	Notification();
}

// 破棄（呼び出し用）
void ANAS::Graphic::Term(){

	ANAS::Log::i( "Graphic", "Terminate" );

	Add(new AnyTasking( boost::bind(&ANAS::Graphic::TermTask, this) ) );

}

// 画面更新（呼び出し用）
void ANAS::Graphic::Swap( float r, float g, float b, float a){

	Add(new AnyTasking( boost::function<void()>(boost::bind(&ANAS::Graphic::SwapTask, this, r, g, b, a) )) );

}

// OpenGLへ移譲される初期化関数
void ANAS::Graphic::InitTask(){

	ANAS::Log::i("EGL Task", "Init");

	const EGLint attribute[] = {
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_NONE
	};
	EGLConfig eglConfig;
	EGLint numConfigs;
	EGLint Format;

	// Display
	eglDisplay = eglGetDisplay( EGL_DEFAULT_DISPLAY );
	eglInitialize(eglDisplay, 0, 0);

	// Config
	eglChooseConfig( eglDisplay, attribute, &eglConfig, 1, &numConfigs );

	eglGetConfigAttrib( eglDisplay, eglConfig, EGL_NATIVE_VISUAL_ID, &Format );

	// Buffer
	ANativeWindow_setBuffersGeometry( pWindow, 0, 0, Format );

	// 
	eglSurface = eglCreateWindowSurface( eglDisplay, eglConfig, pWindow, NULL );
	
	// "OpenGLES"を指定
	eglBindAPI( EGL_OPENGL_ES_API );

	// GLES2.0対応のコンテキストを選択
	EGLint ContextAttrib[] = {
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};
	eglContext = eglCreateContext( eglDisplay, eglConfig, NULL, ContextAttrib );


	// 標準として設定
	if (eglMakeCurrent( eglDisplay, eglSurface, eglSurface, eglContext ) == EGL_FALSE) {

		ANAS::Log::i("EGL Task", "Init Failed");
	}

	
	eglQuerySurface( eglDisplay, eglSurface, EGL_WIDTH, &Width );
	eglQuerySurface( eglDisplay, eglSurface, EGL_HEIGHT, &Height );
	
	ANAS::Log::i("GRAPHIC", (boost::format("W:%1%, H:%2%")%Width%Height).str().c_str() );

	glViewport( 0, 0, Width, Height);

	
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
					
}

// OpenGLへ破棄を委譲する
void ANAS::Graphic::TermTask(){

	ANAS::Log::i("EGL Task", "Term");

	// 関連付けを解除
	eglMakeCurrent( eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT );

	if( eglContext != EGL_NO_CONTEXT ){
		eglDestroyContext( eglDisplay, eglContext );
	}
	if( eglSurface != EGL_NO_SURFACE ){
		eglDestroySurface( eglDisplay, eglSurface );
	}

	eglTerminate( eglDisplay );

	eglDisplay = EGL_NO_DISPLAY;
	eglSurface = EGL_NO_SURFACE;
	eglContext = EGL_NO_CONTEXT;
}


// OpenGLへ画面更新を委譲する
void ANAS::Graphic::SwapTask( float r, float g, float b, float a){
	
	eglSwapBuffers(eglDisplay, eglSurface);
					
	glClearColor( r, g, b, a );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}