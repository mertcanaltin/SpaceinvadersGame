#include "MenuManager.h"
#include "Config.h"
#include "GameOverScene.h"
#include "GameScene.h"
#include "PlayScene.h"

USING_NS_CC;


MenuManager* MenuManager::_instance = nullptr;

MenuManager* MenuManager::instance() {
	if (_instance == nullptr) {
		_instance = new MenuManager();
	}
	return _instance;
}

MenuManager::MenuManager()
{

}

void MenuManager::switchScene(int nScene)
{
    //ekran geçişlerini sağlar örneğin öldüğümüz zaman gameover ekranında ana menüye dönmek için bir switchScene sağlar
	switch (nScene)
	{
        case SCENE_PLAY_MENU:
        {
            auto scene = PlayScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(153, 0, 204)));
            break;
        }
        case SCENE_GAME_PLAY:
        {
            auto scene = GameScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 255, 0)));
            break;
        }
		case SCENE_GAME_OVER:
		{
			auto scene = GameOverScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(224, 30, 30)));
			break;
		}
		
		default:
			return;
	}
}
//quit
void MenuManager::quit()
{
	Director::getInstance()->end();
}

MenuManager::~MenuManager()
{

}
