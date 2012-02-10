
#ifndef __DEFINED_ANAS_TASK__
#define __DEFINED_ANAS_TASK__

#include <pthread.h>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/shared_ptr.hpp>

#include "log.h"

namespace ANAS {

	/**
	 * タスク処理用基底クラス
	 * @author コガラシ
	*/
	class Task {
		public:

			Task(){}
			virtual ~Task(){}

			// virtual
			virtual void Run() = 0;
	};

	/**
	 * スケジュールへ簡単に登録できるようにするためのクラス
	 * @author コガラシ
	 */
	class AnyTasking : public ANAS::Task {
		public:
			boost::function<void()> holder;

			/**
			 * コンストラクタ
			 * @param function 実行させたい関数（boost:bindとboost:functionを使う）
			 */
			AnyTasking( boost::function<void()> function ){
				holder = function;
			}

			/**
			 * スケジューラ用
			 */
			inline void Run(){
				holder();
			}
	};


	/**
	 * タスク管理クラス
	 * @author コガラシ
	*/
	class TaskScheduler {

		private:
			std::list< Task *>	TaskList;
			
			// therad
			typedef				boost::shared_ptr<boost::thread> SPTHREAD;
			SPTHREAD			ExecuteThread;
			boost::mutex		LockMutex;
			bool				isLive;
			bool				isSleep;

			boost::mutex		SleepMutex;
			boost::condition	SleepCondition;


			void TaskExecute();

		public:

			// コンストラクタ
			TaskScheduler();

			// デストラクタ
			virtual ~TaskScheduler();

			/**
			 * タスクの追加
			 */
			void Add( Task* );

			/**
			 * 登録されているタスクを消去
			 */
			void Clear();

			/**
			 * スケジューラが待機状態か？
			 * @return TRUE:待機中 FALSE:仕事中
			 */
			bool CheckSleep();
	};
}

#endif /* __DEFINED_ANAS_TASK__ */