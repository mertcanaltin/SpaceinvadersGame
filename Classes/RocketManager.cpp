#include "RocketManager.h"
#include "Config.h"
#include "GameScene.h"


USING_NS_CC;

RocketManager* RocketManager::_instance = nullptr;

RocketManager* RocketManager::instance()
{
    if (_instance == nullptr) {
        _instance = new RocketManager();
    }
    return _instance;
}

RocketManager::RocketManager()
{
   
}

void RocketManager::update(float dt)
{
	std::list<Rocket*>::iterator it;
	std::list<Rocket*> removeArray;
	for (it = pRockets.begin(); it != pRockets.end(); ++it) {
		Rocket* pRocket = *it;
		float fRocketY = pRocket->getPositionY();
        
        //roketi y noktasına fırlatır
		pRocket->setPositionY(fRocketY + ROCKET_DELTA_Y);
        // Roket ekrandan çıkmışsa, ana öğeden kaldır
		if (fRocketY > originY + visibleHeight + ROCKET_HEIGHT)
		{
			pGameScene->removeChild(pRocket);
			removeArray.push_back(pRocket);
			addToPool(pRocket);
		}
	}
	
    //roket dizisi
	for (it = removeArray.begin(); it != removeArray.end(); ++it) {
		pRockets.remove(*it);
	}
}

void RocketManager::launch(float launchX, float launchY)
{
    //roket fırlatır
	SimpleRocket* pRocket = _rocketPool.getOne();
	pRocket->setPosition(Vec2(launchX, launchY));
	this->pGameScene->addChild(pRocket);
	pRockets.push_back(pRocket);
        
}

void RocketManager::initialize(float visibleWidth, float visibleHeight, float originX, float originY)
{
    // roket yaratır
    //   IObjectManager.h
    IObjectManager::initialize(visibleWidth, visibleHeight, originX, originY);
}

void RocketManager::addToPool(Rocket* pRocket)
{
    //roket havuzuna geri döner
	_rocketPool.returnObject((SimpleRocket*)pRocket);
    
}

RocketManager::~RocketManager()
{
    //yok et
	_rocketPool.destroy();
}
