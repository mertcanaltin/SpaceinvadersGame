#ifndef PlayScene_h
#define PlayScene_h

#include <stdio.h>

//başlangıç ekranı ve menü sahne callbakleri

class PlayScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
   
    CREATE_FUNC(PlayScene);

private:
    //ana ekrandan geçiş voidleri
   // void menuExitCallback(Ref* sender);
    //void menuRetryCallback(Ref* sender);
    void menuPlayGameCallback(Ref* sender);
};




#endif /* PlayScene_h */
