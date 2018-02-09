#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

struct point
{
	int x, y;
};

int main()
{
	srand(time(0));


	RenderWindow app(VideoMode(400, 533), "Doodle Game");
	app.setFramerateLimit(60);

	Texture t1, t2, t3;
	t1.loadFromFile("./assets/images/background.png");
	t2.loadFromFile("./assets/images/platform.png");
	t3.loadFromFile("./assets/images/doodle.png");

	Sprite sBackground(t1), sPlatform(t2), sDoodle(t3);

	point plat[20];

	for (int i = 0; i < 10; i++)
	{
		plat[i].x = rand() % 400;
		plat[i].y = rand() % 533;
	}

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				app.close();
			}
			app.draw(sBackground);
			app.draw(sDoodle);
			for (int i = 0; i < 10; i++)
			{
				sPlatform.setPosition(plat[i].x, plat[i].y);
				app.draw(sPlatform);
			}
			app.display();
		}
	}

	return 0;
}