#include "Enemy4.h"
#include <SFML/Graphics.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace sf;

Enemy4::Enemy4(Texture *texture, Vector2u windowSize)
{
	this->HP = 2;

	this->shape.setTexture(*texture);
	this->shape.setScale(0.2f, 0.2f);
	this->dir = 1;
	this->shape.setPosition(rand() % (int)(windowSize.x - this->shape.getGlobalBounds().height), 0);
}


Enemy4::~Enemy4()
{
}
