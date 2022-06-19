#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

#include"ObjectToGet.h"

#pragma once
class Speed_Increasing_Mixture :public ObjectToGet {
public:
	Speed_Increasing_Mixture(sf::Texture& tex);
	void updateAnimation(float dt);
	void DrawTo(sf::RenderWindow& w);

	void interaction_with_player(Player& p);
};

