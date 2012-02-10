
#include <unistd.h>
#include <pthread.h>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/shared_ptr.hpp>

#include "ThreadBase.h"

namespace ANAS{
	class ThreadBody {

		private:
			boost::shared_ptr< boost::thread >	pThread;
			boost::mutex						LockMutex;
			bool								isLive;

			ANAS::Runnable						*pRunnable;

		public:
			ThreadBody( ANAS::Runnable *_run ){

				pRunnable = _run;

				isLive = true;
				pThread = boost::shared_ptr<boost::thread>( new boost::thread( boost::bind( &ANAS::ThreadBody::Run, this ) ) );

			}
			~ThreadBody(){

				{
					boost::mutex::scoped_lock Lock( LockMutex );
					isLive = false;
				}

				pThread->join();
			}

			void Run(){

				while(isLive){
					{
						boost::mutex::scoped_lock Lock( LockMutex );

						pRunnable->run();
					}
					usleep(0);
					
				}
			}
	};
}

ANAS::Thread::Thread( ANAS::Runnable *pRunnable ){

	pImpl = new ThreadBody( pRunnable );
}

ANAS::Thread::~Thread(){

	if(pImpl){

		delete pImpl;
	}
}