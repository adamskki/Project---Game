#include "boss.h"
#include <SFML/Graphics.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace sf;


boss::boss(Texture *texture, Vector2u windowSize)
{
	this->HP = 45;

	this->shape.setTexture(*texture);
	this->shape.setScale(0.6f, 0.6f);
	this->pos_x = (this->shape.getGlobalBounds().width)/2;
	this->shape.setPosition((windowSize.x/2)-pos_x, 0);
	this->shootTimerBoss1 = 80;
	this->shootTimerBoss2 = 160;
	this->shootTimerBoss3 = 160;
}


boss::~boss()
{
}
