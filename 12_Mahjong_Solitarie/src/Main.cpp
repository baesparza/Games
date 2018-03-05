#include<time.h>
#include<fstream>
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow app(sf::VideoMode(740, 570), "Mahjong Solitarie");

	sf::Texture t1, t2;
	t1.loadFromFile("./assets/images/background.png");
	t2.loadFromFile("./assets/images/tiles.png");

	sf::Sprite sBackground(t1), sTile(t2);

	while (app.isOpen())
	{
		sf::Event e;
		while (app.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				app.close();
		}

		//////////draw//////////
		app.clear();
		app.draw(sBackground);

		app.display();
	}

	return 0;
}