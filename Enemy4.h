#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace sf;

class Enemy4
{
public:
	Sprite shape;
	int HP;
	int dir;

	Enemy4(Texture *texture, Vector2u windowSize);
	~Enemy4();
};

