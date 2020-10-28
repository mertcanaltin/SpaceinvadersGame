#pragma once

#include <string>

// genişlik, yükseklik
#define HEAVY_ENEMY_WIDTH		48.f
#define HEAVY_ENEMY_HEIGHT		48.f
#define LIGHT_ENEMY_WIDTH		48.f
#define LIGHT_ENEMY_HEIGHT		48.f

#define SPACE_SHIP_WIDTH		48.f
#define SPACE_SHIP_HEIGHT		48.f

#define ROCKET_WIDTH	12.f
#define ROCKET_HEIGHT	24.f

//görüntü kaynakları
#define SPACE_SHIP_PATH "self.png"

#define LIGHT_ENEMY_PATH "enemy1.png"
#define HEAVY_ENEMY_PATH "enemy2.png"


#define ROCKET_PATH "rocket.png"


// roket gücü ve düşman HP (Sağlık Puanı)
//game scene.cpp de tanımlandı
//#define SUPER_ROCKET_POWER 100.f
//#define DEFAULT_ROCKET_POWER 25.f

#define LIGHT_ENEMY_HEALTH 50.f
#define HEAVY_ENEMY_HEALTH 100.f




// sprite türü
#define TAG_GENERAL		0
#define TAG_ENEMY_SHIP	1
#define TAG_ROCKET		2
#define TAG_HEROSHIP	3

#define ENEMY_SHIP_HEAVY 0
#define ENEMY_SHIP_LIGHT 1

// Hareket yer değiştirme
#define SHIP_DELTA_X			20.f
#define SHIP_DELTA_Y			2.1f
#define ROCKET_DELTA_Y			8.f

// Sahne kimlikleri
#define SCENE_PLAY_MENU 0
#define SCENE_GAME_PLAY 1
#define SCENE_GAME_OVER 2


// vuruş hızı
#define ROCKET_RELOAD_RATE		.3f

// arkaplan konumu
#define BACKGROUND_PATH "background.png"

// çarpışma durumu
#define HERO_ENEMY_COLLISION 0
#define ROCKET_ENEMY_COLLISION 1


// yok edilen  düşman saymak için
#define HEAVY_ENEMY_SCORE 1
#define LIGHT_ENEMY_SCORE 1

