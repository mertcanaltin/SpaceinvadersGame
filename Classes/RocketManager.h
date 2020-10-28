#pragma once
#include "Pool.h"
#include "IObjectManager.h"
#include "cocos2d.h"
#include "GameScene.h"

// roket manager fırlatma tanımlamaları ve  IObjectManager::initialize
class RocketManager : public IObjectManager
{
private:
    static RocketManager* _instance;

public:
    static RocketManager* instance();

public:
	RocketManager();
	~RocketManager();
    void update(float dt);
	void initialize(float visibleWidth, float visibleHeight, float originX, float originY);
	void launch(float launchX, float launchY);
    

private:
    //havuza ekleme void
	void addToPool(Rocket* pRocket);
    
private:
    //havuz list
    Pool<SimpleRocket> _rocketPool;
	std::list<Rocket*> pRockets;
    
};

