#pragma once
#include "SFML/graphics.hpp"

class Player
{
public:
	sf::VertexArray* shape;
	void move(sf::Vector2f moveVector);
};

