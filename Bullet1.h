#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace sf;

class Bullet1
{
public:
	Sprite shape;

	Bullet1(sf::Texture *texture, Vector2f pos);
	~Bullet1();
};

