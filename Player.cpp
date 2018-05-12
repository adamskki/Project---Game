#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>


Player::Player(Texture *texture)
{
	this->texture = texture;
	this->shape.setTexture(*texture);
	this->shape.setScale(0.1f, 0.1f);
	this->shape.setPosition(400, 800);
	this->score = 0;
	this->HP = 3;
}


Player::~Player()
{
}
