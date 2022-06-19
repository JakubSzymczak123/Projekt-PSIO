#include "Poisoning_Mixture.h"



Poisoning_Mixture::Poisoning_Mixture(sf::Texture& tex) {
	this->setTexture(tex);
	this->setPosition(rand() % int(1200 - this->getGlobalBounds().width), rand() % int(800 - this->getGlobalBounds().height));

	this->set_obj_id("poisoning_mixture");
};
void Poisoning_Mixture::updateAnimation(float dt) {};
void Poisoning_Mixture::DrawTo(sf::RenderWindow& w) {
	w.draw(*this);
};
void Poisoning_Mixture::interaction_with_player(Player& p) {
	if (this->getGlobalBounds().intersects(p.getGlobalBounds())) {
		if (p.get_health() >= 0)
			p.decrease_health(20);
	}
};