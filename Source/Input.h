

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
	 * Looperの通知を識別するためのID
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
	 * 入力情報の種類
	 */
	enum InputTypeValues {
		IT_KEY = 0,
		IT_MOTION = 1,
	};

	/**
	 * キーの列挙
	 */
	enum InputKeyValues {
		IK_BACK = 0x04
	};


	/**
	 * 入力情報の構造体
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
	 * 入力用クラス
	 * @author コガラシ
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
			 * 初期化<br>
			 * Activityクラスのコールバック関数で扱う
			 * @param pInput AInputQueue
			 */
			void Init( AInputQueue *pInput );


			/**
			 * ポーリング<br>
			 * 自動的に入力データをシステムから取得する
			 */
			void Poll();

			/**
			 * 破棄
			 */
			void Term();

			/**
			 * 入力データを１つずつ取得する
			 * @return 
			 */
			InputData PopState();

			/**
			 * スクリーン座標のオフセット設定
			 */
			void SetScreenOffset( int, int);

	};
}


#endif /* __DEFINED_ANAS_INPUT__ */