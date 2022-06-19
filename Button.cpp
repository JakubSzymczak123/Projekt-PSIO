#include "Button.h"


Button::Button(sf::Color color, sf::Vector2f size, sf::Vector2f pos, std::string font_file) {
	this->setFillColor(color);
	this->setSize(size);
	this->setPosition(pos);


	this->cursor_arrow.loadFromSystem(sf::Cursor::Arrow);
	this->cursor_hand.loadFromSystem(sf::Cursor::Hand);

	if (!this->font.loadFromFile(font_file)) {
		std::cout << "CANNOT LOAD FONT!!" << std::endl;
	}
}

//sprawdzanie czy myszka znajduje sie na przycisku
bool Button::click(sf::RenderWindow& window) {
	if (this->getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
		this->setFillColor(sf::Color(150, 150, 150));
		window.setMouseCursor(cursor_hand);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			return true;
		}
	}
	else {
		window.setMouseCursor(cursor_arrow);
		this->setFillColor(sf::Color::Red);
		return false;
	}
}

/// ustawianie tekstu na przycisku
void Button::set_button_text(const std::string a, int fs) {
	this->text.setFont(font);
	this->text.setString(a);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(fs);
	this->text.setPosition(
		this->getPosition().x + (this->getGlobalBounds().width / 2.f - this->text.getGlobalBounds().width / 2.f),
		this->getPosition().y + (this->getGlobalBounds().height / 2.f - this->text.getGlobalBounds().height / 2.f)
	);
}


//draw
void Button::render(sf::RenderWindow& w) {
	w.draw(*this);
	w.draw(this->text);
}