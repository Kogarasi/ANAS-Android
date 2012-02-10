

#ifndef __DEFINED_MAIN__
#define __DEFINED_MAIN__

#include <android/native_activity.h>

#include "Signal.h"

/**
 * システム初期化のために必要なパラメータ等を受け渡すためのクラス
 * @author コガラシ
 */
class BridgeParameter : public ANAS::Signal {

	public:
		ANativeActivity *activity;
		void			*savedState;
		int				savedStateSize;

	private:
		BridgeParameter();

	public:

		/**
		 * コンストラクタ
		 * @param _activity アクティビティへのポインタ
		 * @param _state ステートデータへのポインタ
		 * @param _statesize ステートデータのサイズ
		 */
		BridgeParameter( ANativeActivity *_activity, void *_state, int _statesize)
			: activity(_activity), savedState(_state), savedStateSize(_statesize)
		{

		}


};

#endif /* __DEFINED_MAIN__ */