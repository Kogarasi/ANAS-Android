
#include <assert.h>
#include <boost/bind.hpp>

#include "RenderList.h"



// コンストラクタ
ANAS::RenderList::RenderList(){

	isLive = true;
	
	// Start Thread
	ExecuteThread = SPTHREAD( new boost::thread( boost::bind( &ANAS::RenderList::RenderingThread, this ) ) );
	_assert( ExecuteThread != NULL );

}

// デストラクタ
ANAS::RenderList::~RenderList(){

	{
		boost::mutex::scoped_lock EnableLock( LockMutex );
		isLive = false;		// 終了宣言
	}

	ExecuteThread->join();
}


// "Finish" -> "Yet"
void ANAS::RenderList::MoveToYetFromFinish(){

	boost::mutex::scoped_lock EnableLock( LockMutex );

	if(Yet.size() == 0){
		Yet.swap( Finish );
	}
}

void ANAS::RenderList::RenderingThread(){

}