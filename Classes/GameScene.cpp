#include "SimpleAudioEngine.h"
#include "PlayScene.h"
#include "GameScene.h"
#include "HeroManager.h"
#include "HeroShip.h"
#include "Enemy.h"
#include "RocketManager.h"
#include "CollisionManager.h"
#include "Config.h"


USING_NS_CC;

Scene* GameScene::createScene()
{

    
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

	auto layer = GameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);
    return scene;
}

// Dosyalar yokken segfaulting yerine yararlı hata mesajı yazdırır
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// "init" üzerinde örneğinizi başlatmanız gerekir
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("sprites.plist");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// vurulan düşman sayısını bu label da gösteriyorum 
    auto dispLabel = Label::createWithTTF("yok edilen gemi sayısı:", "fonts/arial.ttf", 20);
    if (dispLabel == nullptr)
    {
        printf("'fonts/arial.ttf' is missing.");
    }
    else
    {
        // label'ı ekranın  üst orta kısmına yerleştirir
        
        dispLabel->setPosition(Vec2(origin.x + 500, origin.y + visibleSize.height -30));

        // label'ı bu katmana alt öğe olarak ekler
        this->addChild(dispLabel, 10);
    }


	// arka plan ekler
	auto sprite = Sprite::create(BACKGROUND_PATH);
	if (sprite == nullptr) {
		printf("'background.png' is missing.");
	}
	else
	{
        //  grafiği ekranın ortasına konumlandırır
		sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // etiketi bu katmana alt öğe olarak ekler
		this->addChild(sprite, 0);
        
        
        // sahneden sahneye müzik değişebilir
        
        //müzik ekler preloadBackgroundMusic önceden mp3 dosyasını yükler
        //  CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("gameSong.mp3");
        //müzik ekler playBackgroundMusic müziği oynatır
        // CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("gameSong.mp3");
	}


    m_scoreLabel = Label::createWithTTF("0", "fonts/arial.ttf", 24);
    if (m_scoreLabel == nullptr)
    {
        printf("'fonts/arial.ttf' is missing.");
    }
    else
    {
        // etiketi ekranın ortasına yerleştir
        m_scoreLabel->setPosition(Vec2(
            dispLabel->getPositionX() + dispLabel->getContentSize().width + 5.f,
            dispLabel->getPositionY()));

        // etiketi bu katmana alt öğe olarak ekler
        this->addChild(m_scoreLabel, 10);
    }
    
	

	
	//  oyun
	pHeroManager = HeroManager::instance();
	pEnemyManager = EnemyManager::instance();
	pRocketManager = RocketManager::instance();
	pCollisionManager = CollisionManager::instance();
    //sınıftaki tüm değişken ve fonksiyonlara ulaşabilek için
    pHeroManager->setGameScene(this);
    pEnemyManager->setGameScene(this);
    pRocketManager->setGameScene(this);
    pCollisionManager->setGameScene(this);

	pHeroManager->initialize(visibleSize.width, visibleSize.height, origin.x, origin.y);
	pEnemyManager->initialize(visibleSize.width, visibleSize.height, origin.x, origin.y);
	pRocketManager->initialize(visibleSize.width, visibleSize.height, origin.x, origin.y);

//  olayları ekler 
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();

    return true;
}

void GameScene::update(float dt)
{
    
    //olaylar nesneler ekrana gelir
    pHeroManager->update(dt);
    pEnemyManager->update(dt);
    pRocketManager->update(dt);
    
    
}




bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
    //dokunma başlar
	Vec2 touchLocation = touch->getLocation();
	HeroManager::instance()->onTouchBegan(touchLocation.x, touchLocation.y);
	return true;
}

bool GameScene::onTouchMoved(Touch *touch, Event *event)
{
    //dokunma olduğunda hareket eder
	Vec2 touchLocation = touch->getLocation();
	HeroManager::instance()->onTouchMoved(touchLocation.x, touchLocation.y);
	return true;
}

bool GameScene::onTouchEnded(Touch *touch, Event *event)
{
    //dokunma biter
	Vec2 touchLocation = touch->getLocation();
	HeroManager::instance()->onTouchEnded(touchLocation.x, touchLocation.y);
	return true;
}

// Çarpışma olayı
bool GameScene::onContactBegin(PhysicsContact &contact)
{
	Node* shapeA = contact.getShapeA()->getBody()->getNode();
	Node* shapeB = contact.getShapeB()->getBody()->getNode();

	
    // vakalar
    // heroship: düşmanship => oyun bitti
    // roket: düşman gemisi => düşman vuruldu
	int tagA = shapeA->getTag();
	int tagB = shapeB->getTag();
	int nCollisionCase = -1;
	
    //uzay gemimiz düşmana çarpma olayı 
	if ((tagA == TAG_HEROSHIP && tagB == TAG_ENEMY_SHIP) || 
		(tagB == TAG_HEROSHIP && tagA == TAG_ENEMY_SHIP)) {
		nCollisionCase = HERO_ENEMY_COLLISION;
	}
    //roketin düşman gemisine çarpma olayını tanıması
	if ((tagA == TAG_ROCKET && tagB == TAG_ENEMY_SHIP) || 
		(tagB == TAG_ROCKET && tagA == TAG_ENEMY_SHIP))
	{
		nCollisionCase = ROCKET_ENEMY_COLLISION;
	}

    
	switch (nCollisionCase) {
		case HERO_ENEMY_COLLISION:
		{
            // uzay gemimiz düşmana değdiği anda oyunu bitirmek için gerekli olan çarpışma nesnesi
			HeroShip* pHero = (HeroShip*)(tagA == TAG_HEROSHIP ? shapeA : shapeB);
			EnemyShip* pEnemy = (EnemyShip*)(tagA == TAG_ENEMY_SHIP ? shapeA : shapeB);
			return pCollisionManager->handleHeroEnemyCollision(pHero, pEnemy);
		}
		case ROCKET_ENEMY_COLLISION:
		{
            // giden roketin düşman gemisine çarpma collisionu
			Rocket* pRocket = (Rocket*)(tagA == TAG_ROCKET ? shapeA : shapeB);
			EnemyShip* pEnemy = (EnemyShip*)(tagA == TAG_ENEMY_SHIP ? shapeA : shapeB);
			return pCollisionManager->handleRocketEnemyCollision(pRocket, pEnemy);
		}
            
		default:
		{
			return true;
		}
	}
	return true;
}

// roketler ve özellikleri

int SuperPowerRocket=100;
int defaultRocket=25;


SimpleRocket::SimpleRocket()
   : Rocket(defaultRocket, ROCKET_WIDTH, ROCKET_HEIGHT, ROCKET_PATH)
{
}

// 5 düşman gemisi yok edildiğinde roket gücünün değişmesi için yapılar
//SuperRocket::SuperRocket()
// : Rocket (SuperPowerRocket, ROCKET_WIDTH, ROCKET_HEIGHT, ROCKET_PATH)
//{
//}

// her düşman öldüğünde sayaca 1 ekler skor durumu için de kullanılabilinir
void GameScene::increaseScore(int scorePoint)
{
    int curscore;
     curscore = std::atoi(m_scoreLabel->getString().c_str());
    curscore += scorePoint;
    m_scoreLabel->setString(StringUtils::format("%d", curscore));
    
    
    
    // vurulan gemileri saymak için skor sistemi ile her gemiden 1 puan artarak 5 e geliyor
    //arka planda her 5 adet düşman vurulduğunda sayac sıfırlanıyor ve tekrar 5 e sayıyor
    //bu kısım 5 adet düşman vurulduğu zaman yukarıda ki  roket gücünü değişirmek için  amaçlandı  satır 231 : 245
   
   // if (curscore==5){
       // defaultRocket+=100;
       //basic reset :)
       // m_scoreLabel->setString(StringUtils::format(""));//label a boş değer atamasını kaldırırsam skor saymaya 5 den sonrasına da devam eder ve yok edilen tüm gemileri sayar
      //  return;
    //}
    
    
    
  
   
    return  ;
}
