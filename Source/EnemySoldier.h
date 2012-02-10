
#ifndef __DEFINED_ENEMY_SOLDIER__
#define __DEFINED_ENEMY_SOLDIER__

#include <stdlib.h>

#include "vector.h"
#include "EffectBase.h"
#include "Screen.h"

namespace Enemy {

	enum SoldierAction {
		SA_NONE = 0,
		SA_MOVE,
		SA_ATK,
	};

	class Soldier : public EnemyBase {

		private:
			int Interval;
			int NowAction;

			ANAS::Vector2 Target;

		public:


			// コンストラクタ
			Soldier(float _x, float _y)
			:EnemyBase(_x, _y)
			{
				Power = 1;
				Life = 1;
				HitRange = 48;

				NowAction = SA_NONE;
				Interval = 60*1;

			}

			// デストラクタ
			~Soldier(){}

			void Action(){

				switch( NowAction ){
					case SA_NONE:

						Interval--;
						if(Interval <= 0){
							NowAction = rand()%2 + 1; // 1 or 2

							if( NowAction == SA_MOVE ){
								Target.x = rand()%ANAS::Screen::GameWidth();
								Target.y = rand()%ANAS::Screen::GameHeight();

							}

							Interval = 60;
						}

						break;

					case SA_MOVE:
						Move();
						break;

					case SA_ATK:
						Attack();
						break;
				}


			}

			void Move(){
				ANAS::Vector2 v = Target - Pos;
				float length = v.length();

				if( length < 1.f ){
					Pos = Pos + v;

					NowAction = SA_NONE;
				} else {
					Pos = Pos + v/length;
				}

			}
			void Attack(){
				NowAction = SA_NONE;
			}

	};
}

#endif /* __DEFINED_ENEMY_SOLDIER__ */