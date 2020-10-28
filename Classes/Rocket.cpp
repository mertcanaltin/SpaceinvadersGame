#include "Rocket.h"
#include "Config.h"
//stanımlamalarımı kullanıyorum
Rocket::Rocket(float power, float width, float height, std::string path)
	: SpriteBase(width, height, path)
{
    //sprite tag
	setTag(TAG_ROCKET);
	m_power = power;
}



