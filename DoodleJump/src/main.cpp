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

	const unsigned int number_platforms = 5;

	point plat[number_platforms];

	for (int i = 0; i < number_platforms; i++)
	{
		plat[i].x = rand() % 400;
		plat[i].y = rand() % 533;
	}

	int x = 100, y = 100, h = 200;
	float dx = 0.f, dy = 0.f;

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}

		/////keyboard input///
		if (Keyboard::isKeyPressed(Keyboard::Right))
			x += 3;
		else if (Keyboard::isKeyPressed(Keyboard::Left))
			x -= 3;


		///move on y///
		// dy positive means falling, negative going up
		dy += 0.2f;
		y += dy;

		if (y > 500)
			dy = -10.f;

		///checkout if doodle is on platform////
		for (int i = 0; i < number_platforms; i++)
		{
			if (
				(x + 50 > plat[i].x) && 
				(x + 20 < plat[i].x + 68) &&
				(y + 70 > plat[i].y) &&
				(y + 70 < plat[i].y + 14) &&
				(dy > 0))
			{
				dy = -10.f;
			}
		}

		////move platforms///
		if (y < h)
		{
			for (int i = 0; i < number_platforms; i++)
			{
				y = h;
				plat[i].y = plat[i].y - dy;
				if (plat[i].y > 533) // goes of window
				{
					plat[i].y = 0; // move it to the top
					plat[i].x = rand() % 400; // reset x position
				}
			}
		}


		////draw////
		sDoodle.setPosition(x, y);

		app.draw(sBackground);
		for (int i = 0; i < number_platforms; i++)
		{
			sPlatform.setPosition(plat[i].x, plat[i].y);
			app.draw(sPlatform);
		}
		app.draw(sDoodle);
		app.display();
	}

	return 0;
}