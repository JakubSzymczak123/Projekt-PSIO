#include "Speed_Increasing_Mixture.h"


Speed_Increasing_Mixture::Speed_Increasing_Mixture(sf::Texture& tex) {
	this->setTexture(tex);
	this->setPosition(rand() % int(1200 - this->getGlobalBounds().width), rand() % int(800 - this->getGlobalBounds().height));

	this->set_obj_id("speed_increasing_mixture");
};

void Speed_Increasing_Mixture::updateAnimation(float dt) {};
void Speed_Increasing_Mixture::DrawTo(sf::RenderWindow& w) {
	w.draw(*this);
};

void Speed_Increasing_Mixture::interaction_with_player(Player& p) {
	if (this->getGlobalBounds().intersects(p.getGlobalBounds())) {
		p.change_speed(50.f);
	}
};