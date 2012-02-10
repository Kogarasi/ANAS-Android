

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

			// コンストラクタ
			EffectBase()
				:isLive(true){
			}

			// デストラクタ
			virtual ~EffectBase(){}

			// 仮想関数
			virtual void onCreate() = 0;
			virtual void onMove() = 0;
			virtual void onRender() = 0;
			virtual void onRelease() = 0;

			// 生存フラグ
			void SetFinish(){ isLive = false; }
			inline bool CheckFinish(){ return isLive; }
			inline operator bool(){ return isLive; }
	};

	template <class T>
	class EffectWorker {
		private:
			std::list<T*> InstanceList;

		public:

			// コンストラクタ
			EffectWorker(){}
			// デストラクタ
			~EffectWorker(){
				BOOST_FOREACH( T*instance, InstanceList ){
					delete instance;
				}
			}

			// 生成
			void Create(T& param){
				T* pInstance = new T(param);
				pInstance->onCreate();

				InstanceList.push_back( pInstance );
			}

			// 移動
			void Move(){
				typename std::list<T*>::iterator Ite = InstanceList.begin();
				//std::_List_iterator<T*> Ite = InstanceList.begin();
				
				while( Ite != InstanceList.end() ){

					(*Ite)->onMove();
					
					// 消去
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

			// 描画
			void Render(){

				BOOST_FOREACH( T* instance, InstanceList ){
					instance->onRender();
				}

			}

	};
}

#endif /* __DEFINED_COM_EFFECT_BASE */