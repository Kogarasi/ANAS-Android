

#ifndef __DEFINED_COM_EFFECT_BASE__
#define __DEFINED_COM_EFFECT_BASE__

#include <unistd.h>

#include <list>
#include <iterator>
#include <boost/function.hpp>
#include <boost/foreach.hpp>

namespace Com {


	// prototype
	class EffectBase {
		private:
			bool isLive;

		public:

			// �R���X�g���N�^
			EffectBase()
				:isLive(true){
			}

			// �f�X�g���N�^
			virtual ~EffectBase(){}

			// ���z�֐�
			virtual void onCreate() = 0;
			virtual void onMove() = 0;
			virtual void onRender() = 0;
			virtual void onRelease() = 0;

			// �����t���O
			void SetFinish(){ isLive = false; }
			inline bool CheckFinish(){ return isLive; }
			inline operator bool(){ return isLive; }
	};

	template <class T>
	class EffectWorker {
		private:
			std::list<T*> InstanceList;

		public:

			// �R���X�g���N�^
			EffectWorker(){}
			// �f�X�g���N�^
			~EffectWorker(){
				BOOST_FOREACH( T*instance, InstanceList ){
					delete instance;
				}
			}

			// ����
			void Create(T& param){
				T* pInstance = new T(param);
				pInstance->onCreate();

				InstanceList.push_back( pInstance );
			}

			// �ړ�
			void Move(){
				typename std::list<T*>::iterator Ite = InstanceList.begin();
				//std::_List_iterator<T*> Ite = InstanceList.begin();
				
				while( Ite != InstanceList.end() ){

					(*Ite)->onMove();
					
					// ����
					if( (**Ite) == false ){
						
						// Release
						(*Ite)->onRelease();

						delete *Ite;
						Ite = InstanceList.erase(Ite);
						continue;
					}

					Ite++;
				}
			}

			// �`��
			void Render(){

				BOOST_FOREACH( T* instance, InstanceList ){
					instance->onRender();
				}

			}

	};
}

#endif /* __DEFINED_COM_EFFECT_BASE */