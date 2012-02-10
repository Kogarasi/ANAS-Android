
#ifndef __DEFINED_ENEMYBASE__
#define __DEFINED_ENEMYBASE__

#include "Texture.h"
#include "Sprite.h"
#include "vector.h"

namespace Enemy {

	enum ENEMY_ID {
		EID_SOLDIER = 0,
		EID_NONE,
	};

	static const char* ImageName[] = {
		"enemy_soldier.png",
	};
	static const int ImageSize = 128;


	class EnemyBase {
			
		protected:
			int Life;
			int Power;
			float HitRange;

			ANAS::Vector2 Pos;

		public:
			bool isDied;

			ANAS::Texture *pTexture;
			ANAS::Sprite *pSprite;


			// コンストラクタ
			EnemyBase( float _x, float _y)
			:Pos(_x, _y), isDied(false)
			{
			}

			// デストラクタ
			virtual ~EnemyBase(){}

			// 行動
			virtual void Action() = 0;

			void Render(){

				pTexture->Set();

				pSprite->Pos[0] = Pos.x;
				pSprite->Pos[1] = Pos.y;

				pSprite->Render();
				
			}
			
			bool HitCheck( float x, float y, float r, int damage ){
				ANAS::Vector2 div(x,y);
				div = div - Pos;

				if( (r+HitRange) >= div.length() ){
					Life -= damage;

					if( Life <= 0){
						isDied = true;
						return true;
					}
				}
				return false;
			}
	};
};

#endif /* __DEFINED_ENEMYBASE__ */