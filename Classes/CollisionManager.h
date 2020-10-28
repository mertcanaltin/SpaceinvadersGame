#pragma once
#include "cocos2d.h"


class GameScene;
class SpriteBase;
class HeroShip;
class EnemyShip;
class Rocket;
//class SuperRocket;
//çarpışma durumlarını yaratmak için tanımlamalar
class CollisionManager
{
private:
	static CollisionManager* _instance;
	GameScene* pGameScene;
public:
	CollisionManager();
	void setGameScene(GameScene* pScene);
	static CollisionManager* instance();
    //düşman tarafından çarpışma veya roket düşman çarpışması
	bool handleHeroEnemyCollision(HeroShip* pHero, EnemyShip* pEnemy);
	bool handleRocketEnemyCollision(Rocket* pRocket, EnemyShip* pEnemy);
  
};

