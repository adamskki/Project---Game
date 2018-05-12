#include "Bullet4.h"
#include <SFML/Graphics.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace sf;

Bullet4::Bullet4(sf::Texture *texture, Vector2f pos_boss)
{
	this->shape.setTexture(*texture);
	this->shape.setScale(0.15f, 0.15f);
	this->shape.setPosition(pos_boss);
	this->dir = rand()%2;
}


Bullet4::~Bullet4()
{
}
