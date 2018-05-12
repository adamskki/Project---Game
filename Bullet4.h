#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace sf;

class Bullet4
{
public:
	Sprite shape;
	int dir;
	Bullet4(sf::Texture *texture, Vector2f pos_boss);
	~Bullet4();
};

