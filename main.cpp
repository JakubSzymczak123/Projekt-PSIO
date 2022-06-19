#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "Game_engine.h"

#include <memory>
#include <iostream>
#include <ctime>




int main() {

	srand(time(NULL));
	Game_engine game;
	game.loop();

	return 0;
}