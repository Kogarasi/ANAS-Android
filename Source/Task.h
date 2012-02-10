
#ifndef __DEFINED_ANAS_TASK__
#define __DEFINED_ANAS_TASK__

#include <pthread.h>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/shared_ptr.hpp>

#include "log.h"

namespace ANAS {

	/**
	 * �^�X�N�����p���N���X
	 * @author �R�K���V
	*/
	class Task {
		public:

			Task(){}
			virtual ~Task(){}

			// virtual
			virtual void Run() = 0;
	};

	/**
	 * �X�P�W���[���֊ȒP�ɓo�^�ł���悤�ɂ��邽�߂̃N���X
	 * @author �R�K���V
	 */
	class AnyTasking : public ANAS::Task {
		public:
			boost::function<void()> holder;

			/**
			 * �R���X�g���N�^
			 * @param function ���s���������֐��iboost:bind��boost:function���g���j
			 */
			AnyTasking( boost::function<void()> function ){
				holder = function;
			}

			/**
			 * �X�P�W���[���p
			 */
			inline void Run(){
				holder();
			}
	};


	/**
	 * �^�X�N�Ǘ��N���X
	 * @author �R�K���V
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

			// �R���X�g���N�^
			TaskScheduler();

			// �f�X�g���N�^
			virtual ~TaskScheduler();

			/**
			 * �^�X�N�̒ǉ�
			 */
			void Add( Task* );

			/**
			 * �o�^����Ă���^�X�N������
			 */
			void Clear();

			/**
			 * �X�P�W���[�����ҋ@��Ԃ��H
			 * @return TRUE:�ҋ@�� FALSE:�d����
			 */
			bool CheckSleep();
	};
}

#endif /* __DEFINED_ANAS_TASK__ */