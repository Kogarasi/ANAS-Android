
#include <assert.h>
#include <boost/bind.hpp>

#include "RenderList.h"



// �R���X�g���N�^
ANAS::RenderList::RenderList(){

	isLive = true;
	
	// Start Thread
	ExecuteThread = SPTHREAD( new boost::thread( boost::bind( &ANAS::RenderList::RenderingThread, this ) ) );
	_assert( ExecuteThread != NULL );

}

// �f�X�g���N�^
ANAS::RenderList::~RenderList(){

	{
		boost::mutex::scoped_lock EnableLock( LockMutex );
		isLive = false;		// �I���錾
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