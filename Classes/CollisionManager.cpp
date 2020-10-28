#include "CollisionManager.h"
#include "Config.h"
#include "GameOverScene.h"
#include "GameScene.h"
#include "SpriteBase.h"
#include "Rocket.h"
#include "MenuManager.h"
#include "Enemy.h"


USING_NS_CC;

//  CollisionManager.cpp çarpışma sağlama ve tepki alma
CollisionManager* CollisionManager::_instance = nullptr;

CollisionManager* CollisionManager::instance() {
	if (_instance == nullptr) {
		_instance = new CollisionManager();
	}
	return _instance;
}

CollisionManager::CollisionManager()
{
	
}

void CollisionManager::setGameScene(GameScene* pScene)
{
    //oyun sahnesi
	pGameScene = pScene;
}

bool CollisionManager::handleHeroEnemyCollision(HeroShip* pHero, EnemyShip* pEnemy)
{
    //game over sahnesi
	pGameScene->stopAllActions();
	MenuManager::instance()->switchScene(SCENE_GAME_OVER);
	return true;
}

bool CollisionManager::handleRocketEnemyCollision(Rocket* pRocket, EnemyShip* pEnemy)
{
   // Enemy.h içeriğinden tanımlamalara ulaşarak
    //if yapısı ile düşman nesnesinin ölüp ekrandan yok olması amaçlanmıştır

    
    
	pEnemy->getHit(pRocket);
	if (pEnemy->isDead())
	{
        //vurulan düşmanı yok eder
		EnemyManager::instance()->kill(pEnemy);
       // skor ekler 
        pGameScene->increaseScore(pEnemy->scorePoint());
	}
    

    
    
    //giden mermi düşman gemisine çarpar
	pGameScene->removeChild(pRocket);
	return true;
}
