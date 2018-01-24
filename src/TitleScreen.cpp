/*
 * TitleScreen.cpp
 *
 */

/*
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <windows.h>
#include "Menu.h"

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Skyland Chronicles");
	Menu menu(window.getSize().x, window.getSize().y);

	window.setKeyRepeatEnabled(false);

	sf::Texture pTexture;
	sf::Sprite playerImage;

	sf::Texture waterMelonTexture;
	sf::Sprite waterMelonImage;

	sf::Texture axeTexture;
	sf::Sprite axeImage;

	sf::Texture hatTexture;
	sf::Sprite hatImage;


	if(!pTexture.loadFromFile("textures/W_Throw05.png"))
		cout << " Error, could not load player image." << endl;

	if(!waterMelonTexture.loadFromFile("textures/i_watermellon.png"))
			cout << " Error, could not load watermelon image." << endl;

	if(!axeTexture.loadFromFile("textures/w_axe.png"))
			cout << " Error, could not load axe image." << endl;

	if(!hatTexture.loadFromFile("textures/e_hat.png"))
			cout << " Error, could not load hat image." << endl;

	playerImage.setTexture(pTexture);
	playerImage.setPosition(200, 400);

	waterMelonImage.setTexture(waterMelonTexture);
	waterMelonImage.setPosition(window.getSize().x * 1/5, window.getSize().y/2);

	axeImage.setTexture(axeTexture);
	axeImage.setPosition(window.getSize().x * 2/5, window.getSize().y/2);

	hatImage.setTexture(hatTexture);
	hatImage.setPosition(window.getSize().x * 3/5, window.getSize().y/2);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		window.clear();

		menu.draw(window);

		window.draw(playerImage);
		window.draw(waterMelonImage);
		window.draw(axeImage);
		window.draw(hatImage);

		window.display();
	}

	return 0;
}
*/
