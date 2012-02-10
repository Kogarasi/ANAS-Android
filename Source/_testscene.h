
#ifndef __DEFINED_TEST_SCENE__
#define __DEFINED_TEST_SCENE__

#include "SceneBase.h"

#include "Simple2D.h"
#include "Sprite.h"
#include "Image.h"
#include "Texture.h"

namespace test {

	/**
	 * ���ؗp�V�[���N���X
	 * @author �R�K���V
	 */
	class testScene : public ANAS::SceneBase {
		private:
			float theta;

			Simple2D *pSimple2D;
			ANAS::Sprite mTestSprite;

			ANAS::Image AndroidImage;
			ANAS::Texture mTestTexture;

		public:

			testScene();
			~testScene();

			// virtual
			void Init();
			void Process();
			void Render();
	};
}


#endif /* __DEFINED_TEST_SCENE__ */
