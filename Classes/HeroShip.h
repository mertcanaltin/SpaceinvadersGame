#pragma once
#include "SpriteBase.h"

// oyun gemisi class ve sprite için tanımlama ayrıca roket gönderme kontrolü için tanımlama
class Rocket;

class HeroShip :
	public SpriteBase
{
public:
	HeroShip();
	Rocket* fire();
};
