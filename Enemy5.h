#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace sf;
class Enemy5
{
public:
	Sprite shape;
	int HP;
	int dir;
	Enemy5(Texture *texture, Vector2u windowSize);
	~Enemy5();
};

