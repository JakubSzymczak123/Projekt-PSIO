#include "Chest.h"



//ustawianie poczatkowych parametrow
Chest::Chest(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) :animation(texture, imageCount, switchTime) {
	this->setTexture(*texture);
	this->setTextureRect({ 0,0,animation.uvRect.width,animation.uvRect.height });
	this->row = 0;
	this->setOrigin((this->getGlobalBounds().left + this->getGlobalBounds().width) / 2, (this->getGlobalBounds().top + this->getGlobalBounds().height) / 2);
	this->setPosition(rand() % int(1200 - this->getGlobalBounds().width), rand() % int(800 - this->getGlobalBounds().height));

	this->set_obj_id("chest");
}

///updatowanie animacji skrzynki
void Chest::updateAnimation(float deltaTime) {
	this->animation.Update(row, deltaTime, 1);
	this->setTextureRect(animation.uvRect);
}



void Chest::DrawTo(sf::RenderWindow& w) {
	w.draw(*this);
}

//dodawanie punktow w przypadku kolizji z graczem
void Chest::interaction_with_player(Player& p) {

	if (intersects == 0 && chest_opened == 0) {
		if (this->getGlobalBounds().intersects(p.getGlobalBounds())) {
			this->row = 1;
			p.add_points(10);
			p.display_points();
			intersects = 1;
			chest_opened = 1;
		}
	}

}