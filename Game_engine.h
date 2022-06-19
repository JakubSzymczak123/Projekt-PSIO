#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include"Animation.h"
#include"Bullet.h"
#include"Button.h"
#include"Chest.h"
#include"Health_Adding_Mixture.h"
#include"ObjectToGet.h"
#include"Player.h"
#include"Poisoning_Mixture.h"
#include"Slime.h"
#include"Speed_Increasing_Mixture.h"
#include"TileMap.h"

#pragma once
class Game_engine {
private:
	sf::RenderWindow window;
	Button play_button;
	Button choose_hero_button_1;
	Button choose_hero_button_2;
	Button choose_hero_button_3;

	sf::RectangleShape s1;

	Button exit;
	Button restart_game_button;

	// objects to get
	std::vector<std::unique_ptr<ObjectToGet>> objects_to_get;

	//enmies
	std::vector<Slime> slimes;

	//mixtures textures
	sf::Texture health_mixture;
	sf::Texture poisoning_mixture;
	sf::Texture speed_incresing_mixture;
	sf::Texture chest_tex;
	sf::Texture slime_tex;
	sf::Texture bowman;
	sf::Texture wizzard;
	sf::Texture evil_wizz_idle;
	sf::Texture evil_wizz_move;
	sf::Texture background;
	sf::Sprite bg;

	//font
	sf::Font font;
	sf::Text win_text;
	sf::Text lose_text;

	//soundbuffer
	sf::SoundBuffer buffer;
	sf::Sound sound;

	TileMap map;

protected:
	//boleans
	bool menu_open = true;
	bool is_bowman = false;
	bool is_wizzard = false;
	bool is_evil_wizzard = false;
	bool can_change_character = true;

public:
	Game_engine();

	void loop();
};

