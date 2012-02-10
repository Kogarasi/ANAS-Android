
#ifndef __DEFINED_ANAS_RESOURCE__
#define __DEFINED_ANAS_RESOURCE__

#include <string>

namespace ANAS {


	/**
	 * �z���_�[�N���X
	 * @author �R�K���V
	 */
	class ResourceHolder {
		public:
			virtual ~ResourceHolder(){}

	};


	/**
	 * �^���ʗp�N���X<br>
	 * �e���v���[�g�Ō^���w�肵��Resource�ɓ�����
	 * @author �R�K���V
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
	 * ���\�[�X�Ǘ��N���X�̎�������
	 * @author �R�K���V
	 */
	class ResourceImpl;

	/**
	 * ���\�[�X�Ǘ��N���X
	 * @author �R�K���V
	 */
	class Resource {
		private:
			ResourceImpl *pImpl;

		public:

			Resource();
			~Resource();

			/**
			 * ���\�[�X�̐ݒ�
			 */
			void Set( const std::string &, ResourceHolder* );

			/**
			 * ���\�[�X�̎擾
			 */
			ResourceHolder* Get( const std::string & );

			/**
			 * ���\�[�X�̊J��
			 */
			void Release( const std::string & );
	};
}


#endif /* __DEFINED_ANAS_RESOURCE__ */