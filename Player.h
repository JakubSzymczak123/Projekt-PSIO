#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

#include"Animation.h"

#pragma once

class Player :public sf::Sprite {

public:

	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Player() {};


	sf::Vector2u animation_frames(int w, int h);


	/// <summary>
	void UpdateHB();
	bool getFaceRight();

	void Update(float deltaTime, sf::Vector2f destination, const sf::RenderWindow& window);

	void DrawTo(sf::RenderWindow& window);

	void change_speed(float a);
	void increase_health(float a);
	void decrease_health(float a);
	void add_points(int a);
	void display_points();
	int get_health();
	void set_speed(float a);

	bool player_win();
	bool player_lose();

protected:


	float health = 200;
	float speed;
	int points = 0;

	sf::RectangleShape HB;

	Animation animation;
	unsigned int row;
	bool faceRight;
};

