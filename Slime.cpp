#include "Slime.h"


Slime::Slime(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) : Player(texture, imageCount, switchTime, speed) {
	this->setPosition(rand() % int(1200 - this->getGlobalBounds().width), rand() % 800 - this->getGlobalBounds().height);
	this->setTexture(*texture);
	this->setTextureRect({ 0,0,32,25 });
	this->setScale(1.3, 1.3);
	this->speed = rand() % 80;
	this->row = 0;
	this->health = 100;
}

//slimes hb
void Slime::UpdateHB() {

	this->HB.setSize({ 40,5 });
	this->HB.setFillColor(sf::Color::Red);
	this->HB.setOutlineThickness(0.5);
	this->HB.setOutlineColor(sf::Color::Black);
	this->HB.setPosition(this->getPosition().x, this->getPosition().y);
	this->HB.setScale({ static_cast<float>(this->health) / 100.f, 1.0f });

	if (this->health <= 0) {
		std::cout << "SLIME IS GONE !!" << std::endl;
		HB.setScale(0.f, 0.f);
	}
}

//ruch przeciwnika opraz update animacji
void Slime::Update(float deltaTime, sf::Vector2f destination) {
	faceRight = 0;
	animation.Update(row, deltaTime, faceRight);
	this->setTextureRect(animation.uvRect);
	if (this->getPosition().x <= destination.x && this->getPosition().y >= destination.y) {
		this->move(speed * deltaTime, -speed * deltaTime);
	}

	else if (this->getPosition().x >= destination.x && this->getPosition().y >= destination.y) { 
		this->move(-speed * deltaTime, -speed * deltaTime);
	}

	if (this->getPosition().x <= destination.x && this->getPosition().y <= destination.y) { 
		this->move(speed * deltaTime, speed * deltaTime);
	}

	else if (this->getPosition().x >= destination.x && this->getPosition().y <= destination.y) { 
		this->move(-speed * deltaTime, speed * deltaTime);
	}
}

void Slime::Draw(sf::RenderWindow& window) {
	window.draw(*this);
	window.draw(this->HB);
}