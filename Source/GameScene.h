
#ifndef __DEFINED_GAME_SCENE__
#define __DEFINED_GAME_SCENE__

#include <boost/thread.hpp>

#include "SceneBase.h"

#include "Simple2D.h"
#include "Sprite.h"
#include "Image.h"
#include "Texture.h"
#include "Time.h"
#include "EffectBase.h"

#include "BombLineEffect.h"

#include "EnemyBase.h"
#include "EnemySoldier.h"

#include "StageLoader.h"

namespace Game {

	const static int TileSize = 64;
	const static int MapX = 14;
	const static int MapY = 9;

	const static int BombLife = 64;
	const static int AttackInterval = 45;

	struct BombData {
		float x;
		float y;

		int life;
	};

	/**
	 * ゲーム本編クラス
	 * @author コガラシ
	 */
	class GameScene : public ANAS::SceneBase {
		private:
			boost::mutex Mutex;

			Simple2D *pSimple2D;
			// Sprite
			ANAS::Sprite mTileSprite;
			ANAS::Sprite mBombSprite;
			ANAS::Sprite mShadowSprite;
			ANAS::Sprite mBombLineSprite;
			ANAS::Sprite mEnemySprite;
			// Image
			ANAS::Image mTileImage;
			ANAS::Image mBombImage;
			ANAS::Image mShadowImage;
			ANAS::Image mBombLineImage;
			ANAS::Image mEnemyImage[1];
			// Texture
			ANAS::Texture mTileTexture;
			ANAS::Texture mBombTexture;
			ANAS::Texture mShadowTexture;
			ANAS::Texture mBombLineTexture;
			ANAS::Texture mEnemyTexture[1];


			std::vector< BombData * > BombList;
			std::list< Enemy::EnemyBase *> EnemyList;

			ANAS::Time Time;

			// エフェクト
			Com::EffectWorker<Effect::BombLine> BombLineEffect;

			int AttackIntervalCounter;
		public:

			GameScene();
			~GameScene();

			// virtual
			void Init();
			void Process();
			void Render();
	};
}


#endif /* __DEFINED_GAME_SCENE__ */
