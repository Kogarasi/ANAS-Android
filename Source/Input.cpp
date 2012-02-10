
#include "Input.h"

#include <boost/bind.hpp>
#include <boost/format.hpp>
#include "log.h"

ANAS::Input::Input():
pInputQueue(NULL), offset_x(0), offset_y(0)
{
	
	// Create Pipe
	pipe(EventPipe);

}

ANAS::Input::~Input(){

	if(isLive == true){
		Term();
	}

}

void ANAS::Input::Init( AInputQueue *_queue ){

	pInputQueue = _queue;
	isLive = true;

	// Start Polling Thread
	PollThread = THREAD_PTR( new boost::thread( boost::bind( &ANAS::Input::Poll, this) ) );

}

void ANAS::Input::Poll(){

	ANAS::Log::i("Input", "entry poll function");

	// Init
	
	pLooper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
	ALooper_addFd(pLooper, EventPipe[1], 1, ALOOPER_EVENT_INPUT, NULL, NULL);

	AInputQueue_attachLooper(pInputQueue, pLooper, INPUT_ID, 0,0);
	//AInputQueue_attachLooper(pInputQueue, pLooper, 1, 0,0);

	//InputKeyData _keytemp;
	//InputMotionData _motiontemp;
	InputData temp;

	// for Signal
	Notification();

	// loop
	while(1){

		// Lock
		//boost::mutex::scoped_lock Lock(Mutex);

		int ident;
		int event;
		int data;
	

		while( (ident = ALooper_pollAll(0, NULL, &event, (void**)&data)) >= 0){
			//ANAS::Log::i("Poll", (boost::format("IDENT:%1% EVENT:%2% DATA:%3%") % ident % event % data).str().c_str());


			// Input
			if(ident == INPUT_ID){

				// 
				AInputEvent *pInputEvent;
				AInputQueue_getEvent(pInputQueue, &pInputEvent);

				// dispatch
				if( AInputQueue_preDispatchEvent(pInputQueue, pInputEvent) ){
					continue;
				}
				
				// Get Event Type
				int EventType = AInputEvent_getType(pInputEvent);

				// Key Events
				if( EventType == AINPUT_EVENT_TYPE_KEY ){

					
					int Action = AKeyEvent_getAction(pInputEvent);
					if( Action == AKEY_EVENT_ACTION_DOWN){

						// Set Data
						temp.KeyChar = AKeyEvent_getKeyCode(pInputEvent);
						temp.isLong = AKeyEvent_getFlags(pInputEvent) & AKEY_EVENT_FLAG_LONG_PRESS;
						temp.InputType = IT_KEY;

						{
							// Lock
							boost::mutex::scoped_lock Lock(Mutex);
							EventStack.push_back(temp);
						}

						//int PhysicalID = AInputEvent_getDeviceId(pInputEvent);
						//boost::format keycode_format("DEV_ID:%1%, KEYCODE:%2%, LONG_PRESS:%3%");
						//ANAS::Log::i("Input Key", (keycode_format % PhysicalID % _keytemp.KeyChar % _keytemp.isLong).str().c_str() );
					}
				}

				// Motion Events
				else if( EventType == AINPUT_EVENT_TYPE_MOTION ){

					int Action = AMotionEvent_getAction( pInputEvent );
				
					temp.InputType = IT_MOTION;
					temp.Pos.x = AMotionEvent_getX( pInputEvent, 0) - offset_x;
					temp.Pos.y = AMotionEvent_getY( pInputEvent, 0) - offset_y;
					temp.ActionType = Action;

					{
						// Lock
						boost::mutex::scoped_lock Lock(Mutex);
						EventStack.push_back( temp );
					}
				}
				


				AInputQueue_finishEvent(pInputQueue, pInputEvent, 1);
			}

			else if(ident == MAIN_ID){
				
				int EventData;
				if( read(EventPipe[0], &EventData, sizeof(EventData) ) == sizeof(EventData) ){

					boost::format command_format("CMD:%1%");
					ANAS::Log::i("Recieve Event", (command_format % EventData).str().c_str() );

				}
			}

		}

		// break
		if(isLive == false){
			break;
		}

		usleep(100);
	}


	// Term
	AInputQueue_detachLooper(pInputQueue);
	ALooper_removeFd(pLooper, EventPipe[0]);
}

void ANAS::Input::Term(){

	{
		boost::mutex::scoped_lock Lock(Mutex);
		isLive = false;
	}

	if(PollThread != NULL){
		PollThread->join();
	}

	pInputQueue = NULL;
}


ANAS::InputData ANAS::Input::PopState(){
	
	// Lock
	boost::mutex::scoped_lock Lock(Mutex);


	InputData _temp = { -1,-1 };

	// Pop
	if( EventStack.size() > 0 ){
		_temp = EventStack.front();
		EventStack.pop_front();
	}

	return _temp;
}

void ANAS::Input::SetScreenOffset( int _x, int _y ){
	
	// Lock
	boost::mutex::scoped_lock Lock(Mutex);

	offset_x = _x;
	offset_y = _y;
}