#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <vector>
#include "Bullet1.h"

using namespace sf;

class Player
{
public:
	Sprite shape;
	Texture *texture;
	int shootTimer = 20;
	std::vector<Bullet1> bullets1;

	int HP;
	int score;


	Player(Texture *texture);
	~Player();
};

