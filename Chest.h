#include"ObjectToGet.h"


#pragma once
class Chest :public ObjectToGet {
public:
	//Chest() {};
	Chest(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);

	void updateAnimation(float deltaTime);

	void DrawTo(sf::RenderWindow& w);

	void interaction_with_player(Player& p);



protected:
	bool intersects = 0;
	bool chest_opened = 0;
	Animation animation;
	unsigned int row;
};

