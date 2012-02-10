

#ifndef __DEFINED_EFFECT_BOMB_LINE__
#define __DEFINED_EFFECT_BOMB_LINE__

#include <unistd.h>

#include "Sprite.h"
#include "EffectBase.h"

namespace Effect {

	class BombLine : public Com::EffectBase {

		public:

			float x;
			float y;
			float theta;
			int life;

			ANAS::Sprite *pSprite;

			// コンストラクタ
			BombLine(){}
			// デストラクタ
			~BombLine(){}

			void onCreate(){}
			void onMove(){

				theta += 0.01f;

				life--;
				if(life<=0){
					SetFinish();
				}

			}
			void onRender(){
				pSprite->Pos[0] = x;
				pSprite->Pos[1] = y;
				pSprite->Rotate = theta;

				pSprite->Render();
			}
			void onRelease(){}
	};
}

#endif /* __DEFINED_EFFECT_BOMB_LINE__ */