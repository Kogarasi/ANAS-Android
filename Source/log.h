

#ifndef __DEFINED_ANAS_LOG__
#define __DEFINED_ANAS_LOG__

#include <android/log.h>

namespace ANAS {

	/**
	 * ログ表示クラス
	 * @author コガラシ
	 */
	class Log {

		public:

			// echo "error"

			/**
			 * "エラー"ステータスでログを表示
			 * @param tag タグ
			 * @param var 本文
			*/
			static void e(const char *tag, const char *var){
				__android_log_print(ANDROID_LOG_ERROR, tag, var);
			}
			
			/**
			 * "情報"ステータスでログを表示
			 * @param tag タグ
			 * @param var 本文
			*/
			static void i(const char *tag, const char *var){
				__android_log_print(ANDROID_LOG_INFO, tag, var);
			}
			
			/**
			 * "デバッグ"ステータスでログを表示
			 * @param tag タグ
			 * @param var 本文
			*/
			static void d(const char *tag, const char *var){
				__android_log_print(ANDROID_LOG_WARN, tag, var);
			}
	};

}


#endif /* __DEFINED_ANAS_LOG__ */
