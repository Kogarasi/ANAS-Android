
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
	 * �V�[���ɕK�v�ȃf�[�^���܂Ƃ߂�R���e�i
	 * @author �R�K���V
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
	 * �V�[���Ǘ��p���N���X
	 * @author �R�K���V
	 */
	class SceneBase {
		friend class SceneManager;

		private:
			bool				isSceneEnd;
			bool				isInitialized;

			/**
			 * �R���e�i��ݒ�
			 */
			inline void SetContainer( SceneContainer * pC ){
				pContainer = pC;
			}

			/**
			 * ���\�[�X�}�l�[�W����ݒ�
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
			 * ����������
			 */
			virtual void Init() = 0;

			/**
			 * �i�s����
			 */
			virtual void Process() = 0;
			/**
			 * �`�揈��
			 */
			virtual void Render() = 0;

			/**
			 * �������̊�����ʒm
			 */
			void SetInitialized(){
				isInitialized = true;
			}

			/**
			 * ���̃V�[���̏I����ʒm
			 */
			void SetSceneEnd(){
				isSceneEnd = true;
			}

			/**
			 * ���̃V�[�����I�����Ă��邩
			 */
			bool CheckSceneEnd(){
				return isSceneEnd;
			}

			/**
			 * �Q�[���S�̂̏I����ʒm
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

			// �R���X�g���N�^
			SceneManager( SceneContainer *pContainer );
			// �f�X�g���N�^
			~SceneManager();

			// �X���b�h�֐�
			void run();
	};
}

#endif /* __DEFINED_ANAS_SCENEBASE__ */