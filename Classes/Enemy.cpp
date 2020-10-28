#include "Enemy.h"
#include "SpriteBase.h"
#include "Config.h"
#include "Rocket.h"
USING_NS_CC;




//  gemisi özellikleri
HeavyEnemyShip::HeavyEnemyShip()
    : EnemyShip(HEAVY_ENEMY_HEALTH, HEAVY_ENEMY_WIDTH, HEAVY_ENEMY_HEIGHT, HEAVY_ENEMY_PATH,HEAVY_ENEMY_SCORE)
{
    
    m_enemyType = ENEMY_SHIP_HEAVY;
}

LightEnemyShip::LightEnemyShip()
    : EnemyShip(LIGHT_ENEMY_HEALTH, LIGHT_ENEMY_WIDTH, LIGHT_ENEMY_HEIGHT, LIGHT_ENEMY_PATH,LIGHT_ENEMY_SCORE)
{
    m_enemyType = ENEMY_SHIP_LIGHT;
}

EnemyShip::EnemyShip(float health, float width, float height, std::string path, int scorePoint)
	: SpriteBase(width, height, path)
{
    //düşman canı ve skor
	m_health = health;
	m_fullHealth = m_health;
	setTag(TAG_ENEMY_SHIP);
    m_scorePoint = scorePoint;
	setFlippedY(true);
    
}

void EnemyShip::getHit(Rocket* pRocket)
{
    //roketi tanıma
    this->m_health -= pRocket->power();
	
}

//can reset
void EnemyShip::reset()
{
	this->m_health = this->m_fullHealth;
	
}

EnemyManager* EnemyManager::_instance = nullptr;

EnemyManager* EnemyManager::instance()
{
    //düşman yoksa üret
    if (_instance == nullptr) {
        _instance = new EnemyManager();
    }
    return _instance;
}

EnemyManager::EnemyManager()
{
}



void EnemyManager::update(float dt)
{
    bool bEnemyExists = false;
    std::list<EnemyShip*>::iterator it;
    std::list<EnemyShip*> removeArray;
    for (it = pEnemies.begin(); it != pEnemies.end(); ++it) {
        EnemyShip* pEnemy = *it;
        float fEnemyY = pEnemy->getPositionY();
        pEnemy->setPositionY(fEnemyY - SHIP_DELTA_Y);
        
        if (pEnemy->getPositionY() < originY - SPACE_SHIP_HEIGHT)
        {
            // düşman görünür alanda değil
            pGameScene->removeChild(pEnemy);
            pEnemy->reset();
            removeArray.push_back(pEnemy);
            addToPool(pEnemy);
        }
        else // düşman görünür alanda
        {
            bEnemyExists = true;
        }
    }

    for (it = removeArray.begin(); it != removeArray.end(); ++it) {
        EnemyShip* pShip = *it;
        pEnemies.remove(pShip);
    }

    if (!bEnemyExists) {
        generateTroop();
    }
}

void EnemyManager::addToPool(EnemyShip* pEnemy)
{
    //havuz
    switch (pEnemy->enemyType()) {
        case ENEMY_SHIP_HEAVY:
        {
            _heavyEnemyPool.returnObject((HeavyEnemyShip*)pEnemy);
            break;
        }
        case ENEMY_SHIP_LIGHT:
        {
            _lightEnemyPool.returnObject((LightEnemyShip*)pEnemy);
            break;
        }
    }
}

void EnemyManager::initialize(float visibleWidth, float visibleHeight, float originX, float originY)
{
    IObjectManager::initialize(visibleWidth, visibleHeight, originX, originY);
    m_level = 0;
    generateTroop();
}

void EnemyManager::levelUp(int level)
{
    //level
    m_level += level;
}



void EnemyManager::generateTroop()
{

    //düşman gemisi üretir
    float xMargin = SPACE_SHIP_WIDTH / 2.f;

    float occu_width = SPACE_SHIP_WIDTH * 3.f / 2.f;
    float occu_height = SPACE_SHIP_HEIGHT * 3.f / 2.f;
    float delta_val = visibleWidth - xMargin * 2.f;
    int col_cnt = (int)(delta_val / occu_width + 1);
    int row_cnt = std::min(++m_level + 1, 1);  // 1 sütun düşman oluştur
    m_level = row_cnt - 1;

    // en fazla 5 sütun kalıbında düşman  oluşabilir oyunun level sistemine geçmesi durumunda buraya müdahale edilebilinir
    for (int j = 0; j < row_cnt; j++)
    {
        for (int i = 0; i < col_cnt; i++)
        {
            int nEnemyType = rand() % 2;
            //rastgele düşman gemisi üretir
            EnemyShip* pEnemy = nullptr;
            if (nEnemyType == ENEMY_SHIP_HEAVY) {
                pEnemy = _heavyEnemyPool.getOne();
            }
            else {
                pEnemy = _lightEnemyPool.getOne();
            }
            pEnemies.push_back(pEnemy);

            pEnemy->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
            pEnemy->setPosition(Vec2(originX + xMargin + occu_width * i,
                visibleHeight + originY + occu_height * j));
            this->pGameScene->addChild(pEnemy);
        }
    }
}

void EnemyManager::kill(EnemyShip* pEnemy)
{
    //düşman gemisini yok eder
    pEnemies.remove(pEnemy);
    this->pGameScene->removeChild(pEnemy);
    pEnemy->reset();
    if (pEnemy->enemyType() == ENEMY_SHIP_HEAVY) {
        _heavyEnemyPool.returnObject((HeavyEnemyShip*)pEnemy);
    }
    else {
        _lightEnemyPool.returnObject((LightEnemyShip*)pEnemy);
    }
}

EnemyManager::~EnemyManager()
{
    _heavyEnemyPool.destroy();
    _lightEnemyPool.destroy();
}
