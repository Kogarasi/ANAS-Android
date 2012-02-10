
#ifndef __DEFINED_ANAS_THREAD__
#define __DEFINED_ANAS_THREAD__

namespace ANAS {
	
	/**
	 * �X���b�h���s�p���N���X
	 * @author �R�K���V
	 */
	class Runnable {
		public:
			virtual void run() = 0;
	};
	
	class ThreadBody;


	/**
	 * �X���b�h�����N���X
	 * @author �R�K���V
	 */
	class Thread {
		
		private:
			ANAS::ThreadBody *pImpl;
		
		public:

			// �R���X�g���N�^
			Thread( Runnable * );

			// �f�X�g���N�^
			~Thread();
	};
}

#endif /* __DEFINED_ANAS_THREAD__ */