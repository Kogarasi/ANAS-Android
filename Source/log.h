

#ifndef __DEFINED_ANAS_LOG__
#define __DEFINED_ANAS_LOG__

#include <android/log.h>

namespace ANAS {

	/**
	 * ���O�\���N���X
	 * @author �R�K���V
	 */
	class Log {

		public:

			// echo "error"

			/**
			 * "�G���["�X�e�[�^�X�Ń��O��\��
			 * @param tag �^�O
			 * @param var �{��
			*/
			static void e(const char *tag, const char *var){
				__android_log_print(ANDROID_LOG_ERROR, tag, var);
			}
			
			/**
			 * "���"�X�e�[�^�X�Ń��O��\��
			 * @param tag �^�O
			 * @param var �{��
			*/
			static void i(const char *tag, const char *var){
				__android_log_print(ANDROID_LOG_INFO, tag, var);
			}
			
			/**
			 * "�f�o�b�O"�X�e�[�^�X�Ń��O��\��
			 * @param tag �^�O
			 * @param var �{��
			*/
			static void d(const char *tag, const char *var){
				__android_log_print(ANDROID_LOG_WARN, tag, var);
			}
	};

}


#endif /* __DEFINED_ANAS_LOG__ */
