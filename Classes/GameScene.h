#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "SpriteBase.h"
#include "Rocket.h"
#include <string>
#include "cocos2d.h"
#include "Config.h"

//oyun ekranı ana değişkenler ve classlar
class EnemyManager;
class HeroManager;
class RocketManager;
class CollisionManager;
class GameScene : public cocos2d::Scene
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();
	virtual void update(float dt);
    void increaseScore(int scorePoint);
    void rocketUpdate ();
	void SetPhysicsWorld(cocos2d::PhysicsWorld *world) { m_sceneWorld = world; };

    
    
	// dokunma olay dinleyicisi
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	bool onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	bool onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	bool onContactBegin(cocos2d::PhysicsContact &contact);
    
    
    

private:
    //label ve manager için tanımlamalar
    cocos2d::Label*                m_scoreLabel;        // score label

	EnemyManager* pEnemyManager;
	HeroManager* pHeroManager;
	RocketManager* pRocketManager;
	CollisionManager* pCollisionManager;
	cocos2d::PhysicsWorld *		m_sceneWorld;
    CREATE_FUNC(GameScene);
};



// roketimiz
class SimpleRocket : public Rocket
{
public:
    SimpleRocket();
    ~SimpleRocket(){ }
    
};

// 5 düşman yk ettikten sonra roket gücü değişimi için oluşturmak istediğim superRocket
//class SuperRocket : public Rocket
//{
//public:
//    SuperRocket();
 //   ~SuperRocket(){ }
    
//};



#endif // __HELLOWORLD_SCENE_H__
