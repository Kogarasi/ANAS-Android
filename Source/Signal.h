
#ifndef __DEFINED_ANAS_SIGNAL__
#define __DEFINED_ANAS_SIGNAL__

#include <boost/thread.hpp>

namespace ANAS {


	/**
	 * �����N���X
	 * @author �R�K���V
	 */
	class Signal {
		private:
			boost::unique_future<void> SyncFuture;
			boost::promise<void> SyncPromise;

		public:

			/**
			 * �R���X�g���N�^
			 */
			Signal(){
				SyncFuture = SyncPromise.get_future();
			}

			/**
			 * �ʒm
			 */
			void Notification(){

				SyncPromise.set_value();
			}

			/**
			 * �҂�
			 */
			void Wait(){

				SyncFuture.get();

			}
	};
}

#endif /* __DEFINED_ANAS_SIGNAL__ */