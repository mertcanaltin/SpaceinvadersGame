#pragma once
#include <string>
#include "SpriteBase.h"
#include "Rocket.h"
#include "Config.h"
#include "Enemy.h"
#include "Pool.h"
#include "IObjectManager.h"

// düşman classları ve geriye değer döndürmesi gerekli olmayan void fonksiyon tanımlamaları
class Rocket;

class EnemyShip : public SpriteBase
{
protected:
	float m_fullHealth;
	float m_health;
	int m_enemyType;
    int m_scorePoint;
	
public:
    //düşman gemisi, tipi  ve config.h de belirtilen skor bedeli için tanımlamalar
	EnemyShip(float health, float width, float height, std::string path,int scorePoint);
	bool isDead() { return m_health <= 0; }
	virtual void getHit(Rocket* pRocket);
	virtual void reset();
	int enemyType() { return m_enemyType; }
    int scorePoint() { return m_scorePoint; }
private:
	
};

//güçlü düşman
class HeavyEnemyShip : public EnemyShip
{

public:
    HeavyEnemyShip();
    ~HeavyEnemyShip(){ }
};

//zayıf düşman
class LightEnemyShip : public EnemyShip
{

   
public:
    LightEnemyShip();
};

//düşman üretimi 
class EnemyManager : public IObjectManager
{
private:
    static EnemyManager* _instance;

public:
    
    static EnemyManager* instance();

public:
    EnemyManager();
    ~EnemyManager();
    void update(float dt);
    void initialize(float visibleWidth, float visibleHeight, float originX, float originY);
    void levelUp(int level=1);
    void kill(EnemyShip* pEnemy);
    
   
private:
    void generateTroop();
    void addToPool(EnemyShip* pEnemy);
private:
    Pool<HeavyEnemyShip> _heavyEnemyPool;
    Pool<LightEnemyShip> _lightEnemyPool;
    std::list<EnemyShip*> pEnemies;
    int m_level;
};
