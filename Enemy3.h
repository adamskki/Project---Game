#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet2.h"
#include <SFML\System.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace sf;

class Enemy3
{
public:
	Sprite shape;
	int shootTimer2 = 20;
	std::vector<Bullet2> bullets2;
	int HP;

	Enemy3(Texture *texture, Vector2u windowSize);
	~Enemy3();
};

