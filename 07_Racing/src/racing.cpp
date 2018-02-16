#include <SFML/Graphics.hpp>
 
using namespace sf;

int main()
{
	RenderWindow app(VideoMode(640,480), "Racing");
	app.setFramerateLimit(60);

	Texture t1, t2;
	t1.loadFromFile("./assets/images/background.png");
	t2.loadFromFile("./assets/images/car.png");

	Sprite sBackground(t1), sCar(t2);

	sCar.setPosition(300,300);


	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}

		/////draw/////
		app.clear(Color::White);
		app.draw(sBackground);

		sCar.setColor(Color::Red);
		app.draw(sCar);

		app.display();
	}

	return 0;
}