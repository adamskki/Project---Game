#pragma 
#include <SFML/Graphics.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace sf;

class bullet3
{
public:
	Sprite shape;

	bullet3(sf::Texture *texture, Vector2f pos_boss);
	~bullet3();
};

