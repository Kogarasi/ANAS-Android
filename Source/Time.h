
#ifndef __DEFINED_ANAS_TIME__
#define __DEFINED_ANAS_TIME__

#include <unistd.h>
#include <time.h>

namespace ANAS {

	/**
	 * タイマークラス
	 * @author コガラシ
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
			 * 前回の呼び出し時間から指定されたsec秒分待機する
			 * @param sec 待機する秒数
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
