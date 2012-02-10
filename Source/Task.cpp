
#include <assert.h>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#include "log.h"
#include "Task.h"


// コンストラクタ
ANAS::TaskScheduler::TaskScheduler(){

	isLive = true;
	isSleep = false;

	// Start Thread
	ExecuteThread = SPTHREAD( new boost::thread( boost::bind( &ANAS::TaskScheduler::TaskExecute, this ) ) );
	_assert( ExecuteThread != NULL );

}

ANAS::TaskScheduler::~TaskScheduler(){

	{
		boost::mutex::scoped_lock EnableLock( LockMutex);
		isLive = false;		// 終了宣言
	}

	ExecuteThread->join();
}

void ANAS::TaskScheduler::TaskExecute(){

	ANAS::Log::i("TaskScheduler", "Start TaskScheduling!");

	while(true == isLive){

		// 登録されているタスク数を確認
		int TaskSize=0;
		{
			boost::mutex::scoped_lock EnableLock( LockMutex );

			TaskSize = TaskList.size();
		}

		if( TaskSize > 0){

			boost::mutex::scoped_lock EnableLock( LockMutex );

			// 先頭のタスクを実行
			TaskList.front()->Run();


			delete TaskList.front();
			TaskList.pop_front();

		} else {

			//ANAS::Log::i("Task Scheduler", "No task queue. I sleep.");

			boost::unique_lock<boost::mutex> SleepLock( SleepMutex );
			{
				boost::mutex::scoped_lock EnableLock( LockMutex );
				isSleep = true;
			}
			SleepCondition.wait( SleepLock );
			{
				boost::mutex::scoped_lock EnableLock( LockMutex );
				isSleep = false;
			}
			

			//ANAS::Log::i("Task Scheduler", "Feel new task. I wake up");
		}

	}
}

void ANAS::TaskScheduler::Add( Task *newTask ){

	// Lock
	boost::mutex::scoped_lock EnableLock( LockMutex );

	// Add
	TaskList.push_back( newTask );

	// Notify
	SleepCondition.notify_all();

}
void ANAS::TaskScheduler::Clear(){
	boost::mutex::scoped_lock EnableLock( LockMutex );

	unsigned int size = TaskList.size();
	for(unsigned int i=0; i<size; i++){
		
		delete TaskList.front();
		TaskList.pop_front();
	}
	
}

bool ANAS::TaskScheduler::CheckSleep(){
	
	boost::mutex::scoped_lock EnableLock( LockMutex );
	return isSleep;
}