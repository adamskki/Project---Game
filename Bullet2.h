#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace sf;


class Bullet2
{
public:
	Sprite shape;

	Bullet2(sf::Texture *texture, Vector2f pos_enemy);
	~Bullet2();
};

