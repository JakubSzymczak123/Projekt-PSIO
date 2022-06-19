#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>


#pragma once
class Bullet
{
public:
	sf::CircleShape shape;
	sf::Vector2f currVelocity;
	float maxSpeed;

	Bullet(float radius = 2.f)
		: currVelocity(0.f, 0.f), maxSpeed(10.f)
	{
		this->shape.setRadius(radius);
		this->shape.setFillColor(sf::Color::Red);
	}
};

