#include "Enemy2.h"
#include <SFML/Graphics.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace sf;

Enemy2::Enemy2(Texture *texture, Vector2u windowSize)
{
	this->HP = 2;
	
	this->shape.setTexture(*texture);
	this->shape.setScale(1.f, 1.f);
	this->shape.setPosition(rand() % (int)(windowSize.x - this->shape.getGlobalBounds().height), 0);
}


Enemy2::~Enemy2()
{
}
