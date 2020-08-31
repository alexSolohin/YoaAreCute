/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cute.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 14:28:56 by alex              #+#    #+#             */
/*   Updated: 2020/08/30 19:33:03 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CUTE__
# define __CUTE__

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "map.h"

#define WIDTH 1200
#define HEIGHT 800

using namespace sf;
using namespace std;

class Player {
	private: float x, y;
	public:
		float w, h, dx, dy, speed;
		int dir, playerScore, health;
		bool life;
		String file;
		Image image;
		Texture texture;
		Sprite sprite;
		Player(String F, float X, float Y, float W, float H)
		{
			dx = 0; dy = 0; speed = 0; dir = 0; playerScore = 0; health = 100;
			life = true;
			file = F;
			w = W; h = H;
			image.loadFromFile("images/" + file);
			image.createMaskFromColor(Color(41, 33, 59));
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			x = X; y = Y;
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}

		void update(float time)
		{
			switch (dir)
			{
				case 0: dx = speed; dy = 0; break;
				case 1: dx = -speed; dy = 0; break;
				case 2: dx = 0; dy = speed; break;
				case 3: dx = 0; dy = -speed; break;
			}

			x += dx * time;
			y += dy * time;

			speed = 0;
			sprite.setPosition(x, y);
			interactionWithMap();
			if (health <= 0) { life = false; speed = 0; };
		}

		void	interactionWithMap()
		{
			for (int i = y / 32; i < (y + h) / 32; i++)
				for (int j = x / 32; j < (x + w) / 32; j++)
				{
					if (TileMap[i][j] == '0')
					{
						if (dy > 0)
							y = i * 32 - h;
						if (dy < 0)
							y = i * 32 + 32;
						if (dx > 0)
							x = j * 32 - w;
						if (dx < 0)
							x = j * 32 + 32;
					}
					if (TileMap[i][j] == 's')
					{
						playerScore++;
						TileMap[i][j] = ' ';
					}
					if (TileMap[i][j] == 'f')
					{
						health -= 40;
						TileMap[i][j] = ' ';
					}
					if (TileMap[i][j] == 'h')
					{
						health += 20;
						TileMap[i][j] = ' ';
					}

				}
		}

		float getPlayerCoordinateX()
		{
			return x;
		}
		float getPlayerCoordinateY()
		{
			return y;
		}
};

#endif
