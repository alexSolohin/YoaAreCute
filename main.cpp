/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 14:32:39 by alex              #+#    #+#             */
/*   Updated: 2020/08/30 19:44:49 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cute.h"
#include "view.h"

int		main()
{
	RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "You are so cute");


	Font font;
	font.loadFromFile("font/CyrilicOld.TTF");
	Text text("", font, 20);
	text.setColor(Color::Red);
	text.setStyle(Text::Bold | Text::Underlined);

	int gameTime = 0;
	Clock gameTimeClock;
	view.reset(FloatRect(0, 0, WIDTH, HEIGHT));
	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	Player p("hero.png", 250, 250, 96.0, 96.0);

	float currentFrame = 0;
	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		// if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();
		// else { view.rotate(0.01); };
		if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();
		else  {view.move(0.1, 0); }
		clock.restart();
		time = time / 800;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (p.life)
		{
			if ((Keyboard::isKeyPressed(Keyboard::Left))) {
				p.dir = 1; p.speed = 0.1;
				currentFrame += 0.005*time;
				if (currentFrame > 3) currentFrame -= 3;
				p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 96, 96, 96));
				getPlayerCoordinateForView(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
			}

			if ((Keyboard::isKeyPressed(Keyboard::Right))) {
				p.dir = 0; p.speed = 0.1;
				currentFrame += 0.005*time;
				if (currentFrame > 3) currentFrame -= 3;
				p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 192, 96, 96));
				getPlayerCoordinateForView(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
			}

			if ((Keyboard::isKeyPressed(Keyboard::Up))) {
				p.dir = 3; p.speed = 0.1;
				currentFrame += 0.005*time;
				if (currentFrame > 3) currentFrame -= 3;
				p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 288, 96, 96));
				getPlayerCoordinateForView(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
			}

			if ((Keyboard::isKeyPressed(Keyboard::Down))) {
				p.dir = 2; p.speed = 0.1;
				currentFrame += 0.005*time;
				if (currentFrame > 3) currentFrame -= 3;
				p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 0, 96, 96));
				getPlayerCoordinateForView(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
			}
		}
		p.update(time);
		viewmap(time);
		// changeview(); //изменение окна
		window.setView(view);
		window.clear(Color(128, 106, 89));

		for(int i = 0; i < HEIGHT_MAP; i++)
			for(int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(0, 0, 32, 32));
				if (TileMap[i][j] == 's') s_map.setTextureRect(IntRect(32, 0, 32, 32));
				if (TileMap[i][j] == '0') s_map.setTextureRect(IntRect(64, 0, 32, 32));
				if (TileMap[i][j] == 'f') s_map.setTextureRect(IntRect(96, 0, 32, 32));
				if (TileMap[i][j] == 'h') s_map.setTextureRect(IntRect(128, 0, 32, 32));
				s_map.setPosition(j * 32, i * 32);
				window.draw(s_map);
			}
			ostringstream playerHealthString, gameTimeString;
			playerHealthString << p.health; gameTimeString << gameTime;
			text.setString("Health: " + playerHealthString.str() + "\nGame time: " + gameTimeString.str());
			text.setPosition(view.getCenter().x - 165, view.getCenter().y - 200);
			window.draw(text);
			window.draw(p.sprite);
			window.display();
	}
}

