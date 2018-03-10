#include <SFML/Graphics.hpp>

const int W = 1200, H = 800;

int main()
{
	sf::RenderWindow app(sf::VideoMode(W, H), "Asteroids");
	app.setFramerateLimit(60);

	sf::Texture t1, t2;

	t1.loadFromFile("./images/spaceship.png");
	t2.loadFromFile("./images/background.jpg");

	sf::Sprite sPlayer(t1), sBackground(t2);

	sPlayer.setTextureRect(sf::IntRect(40,0,40,40));
	sPlayer.setOrigin(20, 20);

	while (app.isOpen())
	{
		sf::Event e;

		while (app.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				app.close();
		}

		/////draw/////
		app.clear();

		app.draw(sBackground);
		app.draw(sPlayer);
		app.display();
	}

	return 0;
}