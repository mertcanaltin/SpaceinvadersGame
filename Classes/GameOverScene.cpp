#include "GameOverScene.h"
#include "GameScene.h"
#include "MenuManager.h"
#include "PlayScene.h"
#include "Config.h"
USING_NS_CC;

Scene* GameOverScene::createScene()
{
	return GameOverScene::create();
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    // super init first
    if ( !Scene::init() )
    {
        return false;
    }

    //game over sahnesi
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //menü butonları ve konumlar

	auto retryItem = MenuItemImage::create(
										"btn_retry_normal.png",
										"btn_retry_down.png",
										CC_CALLBACK_1(GameOverScene::menuRetryCallback, this));

	if (retryItem == nullptr ||
		retryItem->getContentSize().width <= 0 ||
		retryItem->getContentSize().height <= 0)
	{
		printf("'btn_retry_normal.png' or 'btn_retry_down.png' is missing.");
	}
	else
	{
		retryItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		float x = origin.x + visibleSize.width / 2 ;
		float y = origin.y + retryItem->getContentSize().height * 3.8;
		retryItem->setPosition(Vec2(x, y));
	}

    auto exitItem = MenuItemImage::create(
                                           "btn_exit_normal.png",
                                           "btn_exit_down.png",
                                           CC_CALLBACK_1(GameOverScene::menuExitCallback, this));

    if (exitItem == nullptr ||
        exitItem->getContentSize().width <= 0 ||
        exitItem->getContentSize().height <= 0)
    {
		printf("'btn_exit_normal.png' or 'btn_exit_down.png' is missing.");
    }
    else
    {
		exitItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        float x = origin.x + visibleSize.width / 2 ;
        float y = origin.y + exitItem->getContentSize().height *1.8;
        exitItem->setPosition(Vec2(x,y));
    }
    
    auto homeItem = MenuItemImage::create(
                                        "btn_home_normal.png",
                                        "btn_home_down.png",
                                        CC_CALLBACK_1(GameOverScene::menuPlayCallback, this));

    if (homeItem == nullptr ||
        homeItem->getContentSize().width <= 0 ||
        homeItem->getContentSize().height <= 0)
    {
        printf("'btn_home_normal.png' or 'btn_home_down.png' is missing.");
    }
    else
    {
        homeItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + homeItem->getContentSize().height * 2.8;
        homeItem->setPosition(Vec2(x, y));
    }

    // menü oluştur
    auto menu = Menu::create(exitItem, retryItem,homeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 10);

  //label oluşturur

	auto stateLabel = Label::createWithTTF("Collision kodu çalışıyor !", "fonts/arial.ttf", 32);
    
	if (stateLabel == nullptr)
	{
		printf("'fonts/arial.ttf' is missing.");
	}
	else
	{
        // etiketi ekranın ortasına yerleştirin
		stateLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + (visibleSize.height - stateLabel->getContentSize().height) / 1.2));

        // etiketi bu katmana alt öğe olarak ekleyin
		this->addChild(stateLabel, 10);
	}
    
    auto stateLabel2 = Label::createWithTTF("Üzgünüm kaptan! Gemin ağır hasar aldı devam edemiyoruz.", "fonts/arial.ttf", 22);
    
    if (stateLabel2 == nullptr)
    {
        printf("'fonts/arial.ttf' is missing.");
    }
    else
    {
        // etiketi ekranın ortasına yerleştirin
        stateLabel2->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + (visibleSize.height - stateLabel2->getContentSize().height) / 1.3));

        // etiketi bu katmana alt öğe olarak ekleyin
        this->addChild(stateLabel2, 10);
    }

    // arka plan ekler
    auto sprite = Sprite::create("background.png");
    if (sprite == nullptr) {
		printf("'background.png' is missing.");
    }
    else
    {
        // ekranın ortasına konumlan
		sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // hareketli grafiği bu katmana alt öğe olarak ekleyin
        this->addChild(sprite, 0);
    }

    return true;
}

//menü geçişleri sahneler
void GameOverScene::menuExitCallback(Ref* pSender)
{
	MenuManager::instance()->quit();
}

void GameOverScene::menuRetryCallback(Ref* pSender)
{
	MenuManager::instance()->switchScene(SCENE_GAME_PLAY);
}

void GameOverScene::menuPlayCallback(Ref* pSender)
{
    MenuManager::instance()->switchScene(SCENE_PLAY_MENU);
}
