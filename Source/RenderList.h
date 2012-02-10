
#ifndef __DEFINED_ANAS_RENDERLIST__
#define __DEFINED_ANAS_RENDERLIST__


#include <android/native_activity.h>
#include <android/native_window.h>

#include <list>

#include <pthread.h>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/shared_ptr.hpp>



namespace ANAS {

	class RenderItem {
	};

	class RenderList {

		private:
			std::list< RenderItem > Yet;
			std::list< RenderItem > Ready;
			std::list< RenderItem > Finish;

			// therad
			typedef				boost::shared_ptr<boost::thread> SPTHREAD;
			SPTHREAD			ExecuteThread;
			boost::mutex		LockMutex;
			bool				isLive;

		public:

			// コンストラクタ
			RenderList();

			// デストラクタ
			~RenderList();

			void RenderingThread();

			void MoveToYetFromFinish();

	};

}

#endif /* __DEFINED_ANAS_RENDERLIST__ */