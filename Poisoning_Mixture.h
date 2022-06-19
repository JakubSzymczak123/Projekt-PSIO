#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

#include"ObjectToGet.h"


#pragma once
class Poisoning_Mixture :public ObjectToGet {
public:
	Poisoning_Mixture(sf::Texture& tex);
	void updateAnimation(float dt);
	void DrawTo(sf::RenderWindow& w);
	void interaction_with_player(Player& p);

};


