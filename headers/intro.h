#pragma once
#pragma once
#ifndef INTRO_H
#define INTRO_H

bool init_boot(sf::RenderWindow &window, sf::Font *font )
{
	window.clear();
	sf::Clock clock; // starts the clock
	sf::Time elapsed1;
	sf::Text name;
	sf::Texture texture;
	if (!texture.loadFromFile("media/sfml_logo.png"))
	{
		// error...
	}
	sf::RectangleShape logo;
	logo.setSize({ texture.getSize().x+0.f, texture.getSize().y + 0.f });
	logo.setTexture(&texture);
	logo.setOrigin({ logo.getSize().x/2, logo.getSize().y/2 });
	name.setFont(*font);
	name.setString("Powered By");
	name.setCharacterSize(24);
	name.setFillColor(sf::Color::White);
	name.setOutlineColor(sf::Color::Black);
	name.setOutlineThickness(1);
	name.setOrigin(name.getGlobalBounds().width / 2, name.getGlobalBounds().height / 2);
	name.setPosition( window.getSize().x/2, window.getSize().y/2);
	logo.setPosition(name.getPosition().x, name.getPosition().y+ logo.getSize().y*0.1);
	logo.setScale(0.1,0.1);

	window.draw(name);
	window.draw(logo);
	window.display();
	while (elapsed1.asSeconds() < 2.f)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			return 1;
		elapsed1 = clock.getElapsedTime();
	}
	window.clear();
	name.setString("Simofy Presents");
	name.setCharacterSize(24);
	name.setFillColor(sf::Color::White);
	name.setOutlineColor(sf::Color::Black);
	name.setOutlineThickness(1);
	name.setOrigin(name.getGlobalBounds().width / 2, name.getGlobalBounds().height / 2);
	name.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	window.draw(name);
	window.display();
	while (elapsed1.asSeconds() < 5.f)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			return 1;
		elapsed1 = clock.getElapsedTime();
	}
	window.clear();
	name.setString("Bramble Jam");
	name.setCharacterSize(36);
	name.setFillColor(sf::Color::Magenta);
	name.setOutlineColor(sf::Color::Color(20,20,20,255));
	name.setOutlineThickness(1);
	name.setOrigin(name.getGlobalBounds().width / 2, name.getGlobalBounds().height / 2);
	name.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	window.draw(name);
	window.display();
	while (elapsed1.asSeconds() < 7.f)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			return 1;
		elapsed1 = clock.getElapsedTime();
	}


}




#endif