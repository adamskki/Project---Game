#include "heart.h"
#include <SFML/Graphics.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace sf;


heart::heart(Texture *texture, Vector2u windowSize)
{
	this->shape.setTexture(*texture);
	this->shape.setScale(0.3f, 0.3f);
	this->shape.setPosition(rand() % (int)(windowSize.x - this->shape.getGlobalBounds().height), 0);

}


heart::~heart()
{
}
