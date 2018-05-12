#include "Enemy1.h"
#include <SFML/Graphics.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace sf;


Enemy1::Enemy1(Texture *texture,Vector2u windowSize)
{
	this->HPMax = rand() % 3 + 1;
	this->HP = this->HP;
	

	this->shape.setTexture(*texture);
	this->shape.setScale(0.1f, 0.1f);
	this->shape.setPosition(rand() % (int)(windowSize.x - this->shape.getGlobalBounds().height), 0);
	
}



Enemy1::~Enemy1()
{
}
