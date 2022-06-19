#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

#pragma once
class Button :public sf::RectangleShape {
public:
	Button(sf::Color color, sf::Vector2f size, sf::Vector2f pos, std::string font_file);


	bool click(sf::RenderWindow& window);

	//sf::Text get_Text() { return this->text; }

	void set_button_text(const std::string a, int fs);

	void render(sf::RenderWindow& w);


protected:
	sf::Cursor cursor_hand;
	sf::Cursor cursor_arrow;
	sf::Font font;
	sf::Text text;
};

