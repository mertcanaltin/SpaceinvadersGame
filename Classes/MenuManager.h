#pragma once
#include "cocos2d.h"

//sahne geçişleri inin tanımlama
//çıkış
class MenuManager
{
private:
	static MenuManager* _instance;
public:
	MenuManager();
	~MenuManager();
	static MenuManager* instance();
	void switchScene(int nScene);
	void quit();
};

