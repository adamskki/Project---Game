#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace sf;

class heart
{
public:
	Sprite shape;

	heart(Texture *texture, Vector2u windowSize);
	~heart();
};

