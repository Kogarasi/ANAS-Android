
#ifndef __DEFINED_ANAS_TIME__
#define __DEFINED_ANAS_TIME__

#include <unistd.h>
#include <time.h>

namespace ANAS {

	/**
	 * �^�C�}�[�N���X
	 * @author �R�K���V
	 */
	class Time {
		private:
			float prevTime;

		public:
			Time()
			:prevTime(clock()/(float)CLOCKS_PER_SEC)
			{
			}

			/**
			 * �O��̌Ăяo�����Ԃ���w�肳�ꂽsec�b���ҋ@����
			 * @param sec �ҋ@����b��
			 */
			inline void AdjustTime(float sec){
				float _now;

				do {
					_now = (clock()/(float)CLOCKS_PER_SEC);
					usleep( (prevTime+sec-_now)*CLOCKS_PER_SEC );

				}while( prevTime + sec >= _now );

				prevTime = _now;
			}

	};
}


#endif /* __DEFINED_ANAS_TIME__ */
