
#ifndef __DEFINED_ANAS_SIGNAL__
#define __DEFINED_ANAS_SIGNAL__

#include <boost/thread.hpp>

namespace ANAS {


	/**
	 * 同期クラス
	 * @author コガラシ
	 */
	class Signal {
		private:
			boost::unique_future<void> SyncFuture;
			boost::promise<void> SyncPromise;

		public:

			/**
			 * コンストラクタ
			 */
			Signal(){
				SyncFuture = SyncPromise.get_future();
			}

			/**
			 * 通知
			 */
			void Notification(){

				SyncPromise.set_value();
			}

			/**
			 * 待つ
			 */
			void Wait(){

				SyncFuture.get();

			}
	};
}

#endif /* __DEFINED_ANAS_SIGNAL__ */