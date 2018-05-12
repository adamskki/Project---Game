#include "Bullet2.h"
#include <SFML/Graphics.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace sf;


Bullet2::Bullet2(sf::Texture *texture, Vector2f pos_enemy)
{
	this->shape.setTexture(*texture);
	this->shape.setScale(0.15f, 0.15f);
	this->shape.setPosition(pos_enemy);
}


Bullet2::~Bullet2()
{
}
