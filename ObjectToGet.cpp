#include "ObjectToGet.h"


void ObjectToGet::set_rand_position(sf::RenderWindow& window, Player& p) {
	this->setPosition(rand() % int(window.getSize().x - this->getGlobalBounds().width), rand() % int(window.getSize().y - this->getGlobalBounds().height));
	while (this->getGlobalBounds().intersects(p.getGlobalBounds())) {
		this->setPosition(rand() % int(window.getSize().x - this->getGlobalBounds().width), rand() % int(window.getSize().y - this->getGlobalBounds().height));
	}
}
std::string ObjectToGet::get_obj_id() { return this->obj_id; }
void ObjectToGet::set_obj_id(std::string a) { this->obj_id = a; }