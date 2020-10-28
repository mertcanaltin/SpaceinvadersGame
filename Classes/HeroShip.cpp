#include "Config.h"
#include "HeroShip.h"
#include "Rocket.h"
#include "SpriteBase.h"


//kontrol ettiğimiz gemi özellikleri 
HeroShip::HeroShip()
	: SpriteBase(SPACE_SHIP_WIDTH, SPACE_SHIP_HEIGHT, SPACE_SHIP_PATH)
{
	setTag(TAG_HEROSHIP);
}

Rocket* HeroShip::fire()
{

	return nullptr;
}

