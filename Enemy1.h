#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace sf;
class Enemy1
{
public:
	Sprite shape;

	int HP;
	int HPMax;

	Enemy1(Texture *texture, Vector2u windowSize);
	~Enemy1();
};

