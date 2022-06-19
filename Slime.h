#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

#include"Player.h"


#pragma once
class Slime :public Player {

public:
	Slime(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);

	//slimes hb
	void UpdateHB();
	void Update(float deltaTime, sf::Vector2f destination);
	void Draw(sf::RenderWindow& window);
};

