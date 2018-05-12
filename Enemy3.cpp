#include "Enemy3.h"
#include <SFML/Graphics.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace sf;

Enemy3::Enemy3(Texture *texture, Vector2u windowSize)
{
	this->HP = 2;

	this->shape.setTexture(*texture);
	this->shape.setScale(0.4f, 0.4f);
	this->shape.setPosition(rand() % (int)(windowSize.x - this->shape.getGlobalBounds().height), 0);

}


Enemy3::~Enemy3()
{
}
