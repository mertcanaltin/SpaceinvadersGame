
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"
#include "GameScene.h"
#include "MenuManager.h"
#include "PlayScene.h"
#include "Config.h"
USING_NS_CC;

Scene* PlayScene::createScene()
{
    
    return PlayScene::create();
}

// "init" üzerinde örneğinizi başlatmanız gerekir
bool PlayScene::init()
{
    // super init first
    if ( !Scene::init() )
    {
        
        
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

  
    //play butonu

    auto playItem = MenuItemImage::create(
                                        "btn_playGame_Normal.png",
                                        "btn_playGame_down.png",
                                        CC_CALLBACK_1(PlayScene::menuPlayGameCallback, this));

    if (playItem == nullptr ||
        playItem->getContentSize().width <= 0 ||
        playItem->getContentSize().height <= 0)
    {
        printf("'btn_playGame_Normal' or 'btn_playGame_down.png' is missing.");
    }
    else
    {
        playItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        float x = origin.x + visibleSize.width / 2 ;
        float y = origin.y + playItem->getContentSize().height * 1.8;
        playItem->setPosition(Vec2(x, y));
    }
    
    
    auto menu = Menu::create( playItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 10);

    // arkaplan
    auto sprite = Sprite::create("homeBackground.png");
    if (sprite == nullptr) {
        printf("'background.png' is missing.");
    }
    else
    {
       //buton konumları
        sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // sprite'ı bu katmana alt öğe olarak ekler
        this->addChild(sprite, 0);
        
        // müzik ekler    #include "SimpleAudioEngine.h"   kütüphanesinden faydalanarak
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("helloMasomo.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("helloMasomo.mp3");
    }

    return true;
}

// oyun sahnesi gelir

void PlayScene::menuPlayGameCallback(Ref* pSender)
{
    MenuManager::instance()->switchScene(SCENE_GAME_PLAY);
}
