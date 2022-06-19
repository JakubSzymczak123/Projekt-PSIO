#include "Player.h"


Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) : animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->row = 0;
	this->faceRight = 1;


	this->setOrigin((this->getGlobalBounds().left + this->getGlobalBounds().width) / 2, (this->getGlobalBounds().top + this->getGlobalBounds().height) / 2);
	this->setPosition(206.f, 206.f);
	this->setTexture(*texture);
	this->setTextureRect({ 0,0,animation.uvRect.width,animation.uvRect.height });
};

sf::Vector2u Player::animation_frames(int w, int h) {
	sf::Vector2u temp;
	temp.x = w;
	temp.y = h;
	return temp;
}


//healthbar gracza 
void Player::UpdateHB() {

	this->HB.setSize({ 170,20 });
	this->HB.setFillColor(sf::Color::Red);
	this->HB.setOutlineThickness(1.5);
	this->HB.setOutlineColor(sf::Color::Black);
	this->HB.setPosition({ 0,0 });
	this->HB.setScale({ static_cast<float>(this->health) / 200.f, 1.0f });

	if (health <= 0) {
		std::cout << "GAME OVER!!" << std::endl;
		HB.setScale(0.f, 0.f);
	}
}

bool Player::getFaceRight() { return this->faceRight; }


//ruch oraz animacja bohatera
void Player::Update(float deltaTime, sf::Vector2f destination, const sf::RenderWindow& window) {

	bool key_pressed = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::D)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::W)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		key_pressed = true;
	}
	else
		key_pressed = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)
		&& this->getGlobalBounds().left > 0)
	{
		this->move(-speed * deltaTime, 0.f);
		faceRight = 0;
		animation.Update(row, deltaTime, faceRight);
		this->setTextureRect(animation.uvRect);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)
		&& this->getGlobalBounds().left + this->getGlobalBounds().width < window.getSize().x)
	{
		this->move(speed * deltaTime, 0.f);
		faceRight = 1;
		animation.Update(row, deltaTime, faceRight);
		this->setTextureRect(animation.uvRect);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
		&& this->getGlobalBounds().top > 0)
	{
		this->move(0.f, -speed * deltaTime);
		this->setTextureRect(animation.uvRect);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
		&& this->getGlobalBounds().top + this->getGlobalBounds().height < window.getSize().y)
	{
		this->move(0.f, speed * deltaTime);
		this->setTextureRect(animation.uvRect);
	}

	if (key_pressed == false) {
		//this->setTextureRect({ 0,0,animation.uvRect.width,animation.uvRect.height });
		this->row = 0;
	}

}

void Player::DrawTo(sf::RenderWindow& window) {
	window.draw(this->HB);
	window.draw(*this);
}


void Player::change_speed(float a) { this->speed += a; };
void Player::increase_health(float a) { this->health += a; }
void Player::decrease_health(float a) { this->health -= a; /*std::cout << health << std::endl;*/ }
void Player::add_points(int a) { this->points += a; }
void Player::display_points() { std::cout << "SCORED POINTS: " << this->points << std::endl; }
int Player::get_health() { return this->health; }
void Player::set_speed(float a) { this->speed = a; }

bool Player::player_win() {
	if (this->points >= 70) return true;
	else return false;
}
bool Player::player_lose() {
	if (this->get_health() <= 0) return true;
	else return false;
}