#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

#include"Player.h"

#pragma once


///polimorfizm 
class ObjectToGet :public sf::Sprite {
public:
	ObjectToGet() {};
	~ObjectToGet() = default;
	virtual void updateAnimation(float dt) = 0;
	virtual void DrawTo(sf::RenderWindow& w) = 0;
	virtual void interaction_with_player(Player& p) {};

	void set_rand_position(sf::RenderWindow& window, Player& p);
	std::string get_obj_id();
	void set_obj_id(std::string a);

protected:
	std::string obj_id;
};

