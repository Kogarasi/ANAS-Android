
#ifndef __DEFINED_ANAS_THREAD__
#define __DEFINED_ANAS_THREAD__

namespace ANAS {
	
	/**
	 * スレッド実行用基底クラス
	 * @author コガラシ
	 */
	class Runnable {
		public:
			virtual void run() = 0;
	};
	
	class ThreadBody;


	/**
	 * スレッド処理クラス
	 * @author コガラシ
	 */
	class Thread {
		
		private:
			ANAS::ThreadBody *pImpl;
		
		public:

			// コンストラクタ
			Thread( Runnable * );

			// デストラクタ
			~Thread();
	};
}

#endif /* __DEFINED_ANAS_THREAD__ */