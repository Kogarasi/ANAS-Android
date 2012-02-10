

#ifndef __DEFINED_MAIN__
#define __DEFINED_MAIN__

#include <android/native_activity.h>

#include "Signal.h"

/**
 * �V�X�e���������̂��߂ɕK�v�ȃp�����[�^�����󂯓n�����߂̃N���X
 * @author �R�K���V
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
		 * �R���X�g���N�^
		 * @param _activity �A�N�e�B�r�e�B�ւ̃|�C���^
		 * @param _state �X�e�[�g�f�[�^�ւ̃|�C���^
		 * @param _statesize �X�e�[�g�f�[�^�̃T�C�Y
		 */
		BridgeParameter( ANativeActivity *_activity, void *_state, int _statesize)
			: activity(_activity), savedState(_state), savedStateSize(_statesize)
		{

		}


};

#endif /* __DEFINED_MAIN__ */