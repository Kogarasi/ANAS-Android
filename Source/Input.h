

#ifndef __DEFINED_ANAS_INPUT__
#define __DEFINED_ANAS_INPUT__

#include <android/looper.h>
#include <android/input.h>

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

#include "Signal.h"
#include "vector.h"

namespace ANAS {

	/**
	 * Looper�̒ʒm�����ʂ��邽�߂�ID
	 */
	enum LooperEventID {
		MAIN_ID = 1,
		INPUT_ID = 2,
		USER_ID = 3,
	};

	/**
	 * 
	 */
	enum LooperEventMainFlag {
		MF_INPUT_CHANGED,
		MF_INIT_WINDOW,
		MF_TERM_WINDOW,
		MF_WINDOW_RESIZED,
		MF_WINDOW_REDRAW_NEEDED,
		MF_CONTENT_RECT_CHANGED,
		MF_GAINED_FOCUS,
		MF_LOST_FOCUS,
		MF_CONFIG_CHANGED,
		MF_LOW_MEMORY,
		MF_START,
		MF_RESUME,
		MF_SAVE_STATE,
		MF_PAUSE,
		MF_STOP,
		MF_DESTROY,

	};

	/**
	 * ���͏��̎��
	 */
	enum InputTypeValues {
		IT_KEY = 0,
		IT_MOTION = 1,
	};

	/**
	 * �L�[�̗�
	 */
	enum InputKeyValues {
		IK_BACK = 0x04
	};


	/**
	 * ���͏��̍\����
	 */
	typedef struct InputData_tag {
		int InputType;
		
		// KeyState
		int KeyChar;
		bool isLong;

		// MotionState
		ANAS::Vector2 Pos;
		int ActionType;
	} InputData;

	/**
	 * ���͗p�N���X
	 * @author �R�K���V
	 */
	class Input : public Signal {

		private:

			// for thread
			typedef			boost::shared_ptr<boost::thread> THREAD_PTR;
			THREAD_PTR		PollThread;
			bool			isLive;
			boost::mutex	Mutex;

			// for input
			int				EventPipe[2];
			ALooper			*pLooper;
			AInputQueue		*pInputQueue;

			std::list<InputData> EventStack;

			int offset_x;
			int offset_y;

		public:

			Input();
			~Input();
			
			/**
			 * ������<br>
			 * Activity�N���X�̃R�[���o�b�N�֐��ň���
			 * @param pInput AInputQueue
			 */
			void Init( AInputQueue *pInput );


			/**
			 * �|�[�����O<br>
			 * �����I�ɓ��̓f�[�^���V�X�e������擾����
			 */
			void Poll();

			/**
			 * �j��
			 */
			void Term();

			/**
			 * ���̓f�[�^���P���擾����
			 * @return 
			 */
			InputData PopState();

			/**
			 * �X�N���[�����W�̃I�t�Z�b�g�ݒ�
			 */
			void SetScreenOffset( int, int);

	};
}


#endif /* __DEFINED_ANAS_INPUT__ */