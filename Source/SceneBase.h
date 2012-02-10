
#ifndef __DEFINED_ANAS_SCENEBASE__
#define __DEFINED_ANAS_SCENEBASE__

#include <unistd.h>

#include <android/native_activity.h>

#include "Graphic.h"
#include "Input.h"

#include "ThreadBase.h"
#include "Time.h"
#include "Signal.h"
#include "Resource.h"

namespace ANAS {

	class SceneBase;
	class SceneManager;

	/**
	 * シーンに必要なデータをまとめるコンテナ
	 * @author コガラシ
	 */
	class SceneContainer {
		public:
			
			SceneBase			*pStartScene;

			ANAS::Input			*pInput;
			ANAS::Graphic		*pGraphic;

			ANAS::Signal		NotifySignal;

			ANativeActivity		*pActivity;
	};

	/**
	 * シーン管理用基底クラス
	 * @author コガラシ
	 */
	class SceneBase {
		friend class SceneManager;

		private:
			bool				isSceneEnd;
			bool				isInitialized;

			/**
			 * コンテナを設定
			 */
			inline void SetContainer( SceneContainer * pC ){
				pContainer = pC;
			}

			/**
			 * リソースマネージャを設定
			 */
			inline void SetResourceManager( Resource *pResourceMgr ){
				pResource = pResourceMgr;
			}

		protected:

			SceneContainer		*pContainer;
			SceneBase			*pNextScene;

			Resource			*pResource;
			
		public:

			static SceneBase	*pStartScene;

			SceneBase();
			virtual ~SceneBase();

			/**
			 * 初期化処理
			 */
			virtual void Init() = 0;

			/**
			 * 進行処理
			 */
			virtual void Process() = 0;
			/**
			 * 描画処理
			 */
			virtual void Render() = 0;

			/**
			 * 初期化の完了を通知
			 */
			void SetInitialized(){
				isInitialized = true;
			}

			/**
			 * このシーンの終了を通知
			 */
			void SetSceneEnd(){
				isSceneEnd = true;
			}

			/**
			 * このシーンが終了しているか
			 */
			bool CheckSceneEnd(){
				return isSceneEnd;
			}

			/**
			 * ゲーム全体の終了を通知
			 */
			void GameExit(){
				if( pNextScene ){
					delete pNextScene;
					pNextScene = NULL;
				}
				isSceneEnd = true;
			}
	};

	class SceneManager : public Runnable {

		private:
			
			SceneContainer		*pContainer;
			SceneBase			*pScene;
			Thread				*pThread;
			Time				Timer;
			Resource			ResourceManager;

			
			SceneManager();
		public:

			// コンストラクタ
			SceneManager( SceneContainer *pContainer );
			// デストラクタ
			~SceneManager();

			// スレッド関数
			void run();
	};
}

#endif /* __DEFINED_ANAS_SCENEBASE__ */