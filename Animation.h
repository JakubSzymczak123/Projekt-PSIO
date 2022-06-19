#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>




#pragma once
class Animation :public sf::Sprite {
public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Animation() {};

	void Update(int row, float deltaTime, bool faceRight);

public:
	sf::IntRect uvRect;
private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;
};

