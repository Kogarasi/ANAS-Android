
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
	 * �O���t�B�b�N����̒S��������
	 * OpenGL�̏����͂��̃N���X�փ^�X�N��ǉ����čs��
	 * TaskScheduler�N���X��Singal�N���X���p�����Ă���
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
			 * OpenGL�̏�����
			 * @param _window OpenGL���g������Activity��ANativeWindow
			 */
			void Init(ANativeWindow *_window);

			/**
			 * OpenGL�̔j��
			 */
			void Term();

			/**
			 * ��ʂ̍X�V
			 * @param r glClearColor�̐�
			 * @param g glClearColor�̗�
			 * @param b glClearColor�̐�
			 * @param a glClearColor�̃�
			 */
			void Swap(float r, float g, float b, float a);

			/**
			 * �����������̃X���b�h�ڏ��p
			 */
			void InitTask();
			/**
			 * �j�������̃X���b�h�ڏ��p
			 */
			void TermTask();
			/**
			 * ��ʍX�V�̃X���b�h�ڏ��p
			 */
			void SwapTask( float r, float g, float b, float a);

	};
}

#endif /* __DEFINED_ANAS_GRAPHIC__ */