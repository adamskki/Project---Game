#include "Bullet1.h"
#include <SFML/Graphics.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>


Bullet1::Bullet1(sf::Texture *texture, Vector2f pos)
{
	this->shape.setTexture(*texture);
	this->shape.setScale(0.05f, 0.05f);
	this->shape.setPosition(pos);
}


Bullet1::~Bullet1()
{
}
