#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace sf;

class star
{
public:
	Sprite shape;

	star(Texture *texture, Vector2u windowSize);
	~star();
};

