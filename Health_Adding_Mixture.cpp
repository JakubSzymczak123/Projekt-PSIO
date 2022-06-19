#include "Health_Adding_Mixture.h"



Health_Adding_Mixture::Health_Adding_Mixture(sf::Texture& tex) {
	this->setTexture(tex);
	this->setPosition(rand() % int(1200 - this->getGlobalBounds().width), rand() % int(800 - this->getGlobalBounds().height));

	this->set_obj_id("health_adding_mixture");
};

void Health_Adding_Mixture::DrawTo(sf::RenderWindow& w) {
	w.draw(*this);
};


void Health_Adding_Mixture::interaction_with_player(Player& p) {
	if (this->getGlobalBounds().intersects(p.getGlobalBounds())) {
		if (p.get_health() <= 100)
			p.increase_health(20);
	}
};