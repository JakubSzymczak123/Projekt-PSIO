#include "Game_engine.h"


//konstruktor game_engine
//ustawianie wartosci poczatkowych


Game_engine::Game_engine() :window(sf::VideoMode(1200, 800), "Projekt PSiO"),
play_button(sf::Color::Red, { 150,50 }, { float(window.getSize().x / 2 - 75), float(window.getSize().y / 2) }, "font.ttf"),
choose_hero_button_1(sf::Color::Red, { 70,30 }, { float(window.getSize().x / 2 - 150 - 35),600 }, "font.ttf"),
choose_hero_button_2(sf::Color::Red, { 70,30 }, { float(window.getSize().x / 2 - 35) ,600 }, "font.ttf"),
choose_hero_button_3(sf::Color::Red, { 70,30 }, { float(window.getSize().x / 2 + 150 - 35) ,600 }, "font.ttf"),
exit(sf::Color::Red, { 150,50 }, { 525,650 }, "font.ttf"),
restart_game_button(sf::Color::Red, { 150,50 }, { 525,720 }, "font.ttf")
{
	window.setFramerateLimit(60);
	if (!background.loadFromFile("tekstury/background.png")) std::cout << "CANNOT LOAD BG!" << std::endl;
	else {
		bg.setTexture(background);
		bg.setScale(float(window.getSize().x / bg.getGlobalBounds().width), float(window.getSize().y) / bg.getGlobalBounds().height);
	}


	s1.setSize({ 70,70 });
	s1.setFillColor(sf::Color::Transparent);
	s1.setOutlineThickness(2);
	s1.setOutlineColor(sf::Color::Transparent);

	//button texts
	play_button.set_button_text("start", 12);
	choose_hero_button_1.set_button_text("wizzard", 12);
	choose_hero_button_2.set_button_text("archer", 12);
	choose_hero_button_3.set_button_text("ghost", 12);
	exit.set_button_text("exit", 12);
	restart_game_button.set_button_text("restart game", 12);



	//texture loads
	poisoning_mixture.loadFromFile("tekstury/poisoning_mixture.png");
	health_mixture.loadFromFile("tekstury/health_mixture.png");
	speed_incresing_mixture.loadFromFile("tekstury/speed_mixture.png");
	chest_tex.loadFromFile("chest1.png");
	slime_tex.loadFromFile("tekstury/slime_movement2.png");
	bowman.loadFromFile("bowman.png");
	wizzard.loadFromFile("wizzard_animation8x8.png");

	evil_wizz_idle.loadFromFile("tekstury/evil_wizzard_idle.png");
	evil_wizz_move.loadFromFile("tekstury/evil_wizzard_move.png");

	//font load
	font.loadFromFile("font.ttf");

	//text after winnig game
	win_text.setFont(font);
	win_text.setFillColor(sf::Color::Black);
	win_text.setCharacterSize(35);
	win_text.setString("you win");
	win_text.setPosition(600 - win_text.getGlobalBounds().width / 2, 400 - win_text.getGlobalBounds().height / 2);

	lose_text.setFont(font);
	lose_text.setFillColor(sf::Color::Black);
	lose_text.setCharacterSize(35);
	lose_text.setString("you lost");
	lose_text.setPosition(600 - win_text.getGlobalBounds().width / 2, 400 - win_text.getGlobalBounds().height / 2);

	//shoot sound looad
	if (!buffer.loadFromFile("tekstury/shoot_sound.wav")) std::cout << "CANNOT LOAD BUFFER! " << std::endl;
	else this->sound.setBuffer(buffer);
	this->sound.setVolume(20.f);


	// tworzenie obiektow miksturyi skrzynie
	objects_to_get.resize(25);
	for (int i = 0; i < 8; i++) {
		objects_to_get[i] = std::make_unique<Chest>(&chest_tex, sf::Vector2u(5, 2), 0.2);
	}
	for (int i = 8; i < 16; i++) {
		objects_to_get[i] = std::make_unique<Health_Adding_Mixture>(health_mixture);
	}
	for (int i = 16; i < 23; i++) {
		objects_to_get[i] = std::make_unique<Poisoning_Mixture>(poisoning_mixture);
	}
	for (int i = 23; i < 25; i++) {
		objects_to_get[i] = std::make_unique<Speed_Increasing_Mixture>(speed_incresing_mixture);
	}


	// dodawanie slimow do vectora
	for (int i = 0; i < 15; i++) {
		slimes.emplace_back(Slime(&slime_tex, sf::Vector2u(8, 1), 0.25, 100.f));
	}

}


// gloawna petla gry
void Game_engine::loop() {

	///level do Tilemap
	const int level[] =
	{
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,3,3,3,2,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,3,3,3,2,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,3,3,3,3,3,3,3,2,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,3,3,3,3,3,3,3,2,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,3,3,3,3,3,3,3,2,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

	};

	if (!map.load("tekstury/tileset_complete.png", sf::Vector2u(32, 32), level, 38, 25))
		std::cout << "CANNOT LOAD MAP " << std::endl;

	sf::Event ev;
	sf::Time el;
	sf::Clock clock;
	float deltaTime = 0.f;

	//creating game characters

	Player player(&wizzard, sf::Vector2u(8, 1), 0.15, 100.f);
	Player player_bowman(&bowman, sf::Vector2u(8, 1), 0.20, 100.f);
	Player player_evil_wizzard(&evil_wizz_move, sf::Vector2u(8, 1), 0.20, 100.f);


	Animation wizz_animation(&wizzard, sf::Vector2u(8, 1), 0.2);
	wizz_animation.setScale(0.7, 0.7);
	wizz_animation.setPosition(choose_hero_button_1.getPosition().x + choose_hero_button_1.getGlobalBounds().width / 2 - wizz_animation.getGlobalBounds().width / 2, choose_hero_button_1.getPosition().y - wizz_animation.getGlobalBounds().height - 20);

	Animation archer_animation(&bowman, sf::Vector2u(8, 1), 0.2);
	archer_animation.setScale(1.3, 1.3);
	archer_animation.setPosition(choose_hero_button_2.getPosition().x + choose_hero_button_2.getGlobalBounds().width / 2 - archer_animation.getGlobalBounds().width / 2, choose_hero_button_2.getPosition().y - archer_animation.getGlobalBounds().height + 15);

	Animation evil_wizz_animation(&evil_wizz_idle, sf::Vector2u(8, 1), 0.15);
	evil_wizz_animation.setScale(1.2, 1.2);
	evil_wizz_animation.setPosition(choose_hero_button_3.getPosition().x + choose_hero_button_3.getGlobalBounds().width / 2 - evil_wizz_animation.getGlobalBounds().width / 2, choose_hero_button_3.getPosition().y - evil_wizz_animation.getGlobalBounds().height + 35);

	//shooting
	//bullet
	Bullet b1;
	std::vector<Bullet> bullets;

	//Enemy

	int spawnCounter = 20;
	//Vectors
	sf::Vector2f playerCenter;
	sf::Vector2f mousePosWindow;
	sf::Vector2f aimDir;
	sf::Vector2f aimDirNorm;



	while (window.isOpen()) {

		deltaTime = clock.restart().asSeconds();
		el = clock.restart();

		while (window.pollEvent(ev)) {

			if (ev.type == sf::Event::Closed) {
				window.close();
			}

			if (play_button.click(window)) {
				if (is_wizzard == true || is_bowman == true || is_evil_wizzard == true) {
					menu_open = false;
				}
			}

			if (exit.click(window)) {
				window.close();
				//menu_open = true;
				//can_change_character = true;
			}

			
			if (restart_game_button.click(window)) {
				Game_engine g2;
				g2.loop();
			}

			//wybor bohatera
			if (can_change_character) {
				if (choose_hero_button_1.click(window)) {
					is_wizzard = true;
					is_bowman = false;
					is_evil_wizzard = false;
					s1.setPosition(choose_hero_button_1.getPosition().x, choose_hero_button_1.getPosition().y - 80);
					s1.setOutlineColor(sf::Color::Red);
				}

				if (choose_hero_button_2.click(window)) {
					is_bowman = true;
					is_wizzard = false;
					is_evil_wizzard = false;
					s1.setPosition(choose_hero_button_2.getPosition().x, choose_hero_button_2.getPosition().y - 80);
					s1.setOutlineColor(sf::Color::Blue);
				}

				else if (choose_hero_button_3.click(window)) {
					is_evil_wizzard = true;
					is_bowman = false;
					is_wizzard = false;
					s1.setPosition(choose_hero_button_3.getPosition().x, choose_hero_button_3.getPosition().y - 80);
					s1.setOutlineColor(sf::Color::Green);
				}
			}
		}
		// bullet direction 
		mousePosWindow = sf::Vector2f(sf::Mouse::getPosition(window));
		aimDir = mousePosWindow - playerCenter;
		aimDirNorm.x = aimDir.x / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
		aimDirNorm.y = aimDir.y / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

		window.clear(sf::Color::Black);

		//menu poczatkowe
		if (menu_open) {
			window.draw(bg);
			play_button.render(window);
			choose_hero_button_1.render(window);
			choose_hero_button_2.render(window);
			choose_hero_button_3.render(window);

			///update
			window.draw(s1);

			wizz_animation.Update(0, deltaTime, 1);
			wizz_animation.setTextureRect(wizz_animation.uvRect);
			window.draw(wizz_animation);

			archer_animation.Update(0, deltaTime, 1);
			archer_animation.setTextureRect(archer_animation.uvRect);
			window.draw(archer_animation);

			evil_wizz_animation.Update(0, deltaTime, 1);
			evil_wizz_animation.setTextureRect(evil_wizz_animation.uvRect);
			window.draw(evil_wizz_animation);
		}

		//gra
		else if (!menu_open) {
			//loading cursor
			sf::Cursor cursor;
			if (cursor.loadFromSystem(sf::Cursor::Cross)) {
				window.setMouseCursor(cursor);
			}

			window.draw(map);
			can_change_character = false;


			// uzywanie polimorficznego wskaznika
			for (size_t i = 0; i < objects_to_get.size(); i++) {
				objects_to_get[i]->DrawTo(window);
				objects_to_get[i]->updateAnimation(deltaTime);
			//interakcja z bohaterem w zaleznosci od przedmiotu
				//usuwanie miktur oraz dodawanie nowych 
				if (player.getGlobalBounds().intersects(objects_to_get[i]->getGlobalBounds())
					|| player_bowman.getGlobalBounds().intersects(objects_to_get[i]->getGlobalBounds())
					|| player_evil_wizzard.getGlobalBounds().intersects(objects_to_get[i]->getGlobalBounds())) {
					if (is_bowman) {
						objects_to_get[i]->interaction_with_player(player_bowman);
					}
					if (is_wizzard) {
						objects_to_get[i]->interaction_with_player(player);
					}
					else if (is_evil_wizzard) {
						objects_to_get[i]->interaction_with_player(player_evil_wizzard);
					}

					if (objects_to_get[i]->get_obj_id() == "poisoning_mixture") {
						objects_to_get.erase(objects_to_get.begin() + i);
						objects_to_get.emplace_back(std::make_unique<Poisoning_Mixture>(poisoning_mixture));
					}

					if (objects_to_get[i]->get_obj_id() == "speed_increasing_mixture") {
						objects_to_get.erase(objects_to_get.begin() + i);
					}

					else if (objects_to_get[i]->get_obj_id() == "health_adding_mixture") {
						objects_to_get.erase(objects_to_get.begin() + i);
						objects_to_get.emplace_back(std::make_unique<Health_Adding_Mixture>(health_mixture));
					}
				}
			}

			if (is_wizzard) {
				//
				playerCenter = sf::Vector2f(player.getPosition().x + player.getGlobalBounds().width / 2, player.getPosition().y + player.getGlobalBounds().height / 2);

				sf::Vector2f destination = player.getPosition();
				player.Update(deltaTime, destination, window);
				player.UpdateHB();

				player.DrawTo(window);

			

				for (auto& sl : slimes) {
					sl.Update(deltaTime, destination);
					sl.UpdateHB();
					sl.DrawTo(window);
					if (player.getGlobalBounds().intersects(sl.getGlobalBounds()))
						if (player.get_health() >= 0) player.decrease_health(1);
				}

				for (size_t i = 0; i < bullets.size(); i++)
				{
					window.draw(bullets[i].shape);
					sound.play();
				}
				if (player.player_win()) {
					//window.clear(sf::Color::Black);
					player.set_speed(0.f);
					for (auto& el : slimes) { el.set_speed(0.f); }
					window.draw(win_text);
					exit.render(window);
					restart_game_button.render(window); // restart game
				}
				else if (player.player_lose()) {
					player.set_speed(0.f);
					for (auto& el : slimes) { el.set_speed(0.f); }
					window.draw(lose_text);
					exit.render(window);
					restart_game_button.render(window); //try to restart game
				}

			}

			if (is_bowman) {
				playerCenter = sf::Vector2f(player_bowman.getPosition().x + player_bowman.getGlobalBounds().width / 2, player_bowman.getPosition().y + player_bowman.getGlobalBounds().height / 2);

				sf::Vector2f destination = player_bowman.getPosition();
				player_bowman.Update(deltaTime, destination, window);
				player_bowman.UpdateHB();

				player_bowman.DrawTo(window);

				for (auto& sl : slimes) {
					sl.Update(deltaTime, destination);
					sl.UpdateHB();
					sl.DrawTo(window);
					if (player_bowman.getGlobalBounds().intersects(sl.getGlobalBounds()))
						if (player_bowman.get_health() >= 0) player_bowman.decrease_health(1);
				}

				for (size_t i = 0; i < bullets.size(); i++)
				{
					window.draw(bullets[i].shape);
					sound.play();
				}

				if (player_bowman.player_win()) {
					player_bowman.set_speed(0.f);
					for (auto& el : slimes) { el.set_speed(0.f); }
					window.draw(win_text);
					exit.render(window);
					restart_game_button.render(window); //try to restart game
				}
				else if (player_bowman.player_lose()) {
					player_bowman.set_speed(0.f);
					for (auto& el : slimes) { el.set_speed(0.f); }
					window.draw(lose_text);
					exit.render(window);
					restart_game_button.render(window); //try to restart game
				}
			}

			else if (is_evil_wizzard) {
				playerCenter = sf::Vector2f(player_evil_wizzard.getPosition().x + player_evil_wizzard.getGlobalBounds().width / 2, player_evil_wizzard.getPosition().y + player_evil_wizzard.getGlobalBounds().height / 2);

				sf::Vector2f destination = player_evil_wizzard.getPosition();
				player_evil_wizzard.Update(deltaTime, destination, window);
				player_evil_wizzard.UpdateHB();

				player_evil_wizzard.DrawTo(window);

				for (auto& sl : slimes) {
					sl.Update(deltaTime, destination);
					sl.UpdateHB();
					sl.DrawTo(window);
					if (player_evil_wizzard.getGlobalBounds().intersects(sl.getGlobalBounds()))
						if (player_evil_wizzard.get_health() >= 0) player_evil_wizzard.decrease_health(1);
				}

				for (size_t i = 0; i < bullets.size(); i++)
				{
					window.draw(bullets[i].shape);
					sound.play();
				}

				if (player_evil_wizzard.player_win()) {
					//window.clear(sf::Color::Black);
					player_evil_wizzard.set_speed(0.f);
					for (auto& el : slimes) { el.set_speed(0.f); }
					window.draw(win_text);
					exit.render(window);
					restart_game_button.render(window); //try to restart game
				}
				else if (player_evil_wizzard.player_lose()) {
					player_evil_wizzard.set_speed(0.f);
					for (auto& el : slimes) { el.set_speed(0.f); }
					window.draw(lose_text);
					exit.render(window);
					restart_game_button.render(window); //try to restart game
				}
			}

			//exit.render(window);

			//shooting engine
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				b1.shape.setPosition(playerCenter);
				b1.currVelocity = aimDirNorm * b1.maxSpeed;

				bullets.push_back(Bullet(b1));
			}

			for (size_t i = 0; i < bullets.size(); i++)
			{
				bullets[i].shape.move(bullets[i].currVelocity);

				//Out of bounds
				if (bullets[i].shape.getPosition().x < 0 || bullets[i].shape.getPosition().x > window.getSize().x
					|| bullets[i].shape.getPosition().y < 0 || bullets[i].shape.getPosition().y > window.getSize().y)
				{
					bullets.erase(bullets.begin() + i);
				}
				else
				{
					//enemy collision
					for (size_t k = 0; k < slimes.size(); k++)
					{
						if (bullets[i].shape.getGlobalBounds().intersects(slimes[k].getGlobalBounds()))
						{
							bullets.erase(bullets.begin() + i);
							slimes[k].decrease_health(5);
							//erasing slime having less than 0 health
							if (slimes[k].get_health() <= 0) {
								slimes.erase(slimes.begin() + k);
							}
							break;
						}
					}
				}
			}

		}

		window.display();
	}
}