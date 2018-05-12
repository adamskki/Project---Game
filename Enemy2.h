#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace sf;

class Enemy2
{
public:
	Sprite shape;

	int HP;
	
	Enemy2(Texture *texture, Vector2u windowSize);
	~Enemy2();
};

