#pragma once
#include <SFML/Graphics.hpp>
#include "bullet3.h"
#include "Bullet4.h"
#include <SFML\System.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace sf;
using namespace std;
class boss
{
public:
	Sprite shape;
	int shootTimerBoss1;
	int shootTimerBoss2;
	int shootTimerBoss3;
	std::vector<bullet3> BulletsBoss1;
	std::vector<bullet3>BulletsBoss2;
	std::vector<Bullet4>BulletsBoss3;
	std::vector<Bullet4>BulletsBoss4;
	int pos_x;
	int HP;

	boss(Texture *texture, Vector2u windowSize);
	~boss();
};

