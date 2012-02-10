
#ifndef __DEFINED_ANAS_RESOURCE__
#define __DEFINED_ANAS_RESOURCE__

#include <string>

namespace ANAS {


	/**
	 * ホルダークラス
	 * @author コガラシ
	 */
	class ResourceHolder {
		public:
			virtual ~ResourceHolder(){}

	};


	/**
	 * 型識別用クラス<br>
	 * テンプレートで型を指定してResourceに投げる
	 * @author コガラシ
	 */
	template< class T >
	class ResourceItem : public ResourceHolder {
		private:
			T *holder;
		public:

			ResourceItem( T *item )
			: holder(item)
			{

			}

			~ResourceItem(){
				delete holder;
			}

			T *Get(){
				return holder;
			}

	};
	
	/**
	 * リソース管理クラスの実装部分
	 * @author コガラシ
	 */
	class ResourceImpl;

	/**
	 * リソース管理クラス
	 * @author コガラシ
	 */
	class Resource {
		private:
			ResourceImpl *pImpl;

		public:

			Resource();
			~Resource();

			/**
			 * リソースの設定
			 */
			void Set( const std::string &, ResourceHolder* );

			/**
			 * リソースの取得
			 */
			ResourceHolder* Get( const std::string & );

			/**
			 * リソースの開放
			 */
			void Release( const std::string & );
	};
}


#endif /* __DEFINED_ANAS_RESOURCE__ */