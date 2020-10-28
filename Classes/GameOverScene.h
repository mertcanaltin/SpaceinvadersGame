#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	
    // "statik oluşturma ()" yöntemini manuel olarak uygular
    CREATE_FUNC(GameOverScene);

private:
    //game overiçin  callback
	void menuExitCallback(Ref* sender);
	void menuRetryCallback(Ref* sender);
    void menuPlayCallback(Ref* sender);
};

#endif // __HELLOWORLD_SCENE_H__
