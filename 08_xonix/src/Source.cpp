#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

const unsigned int M = 20, N = 40;

int grif[M][N];
const unsigned int TS = 18; // tile size


int main()
{
	srand(time(0));

	RenderWindow window(VideoMode(N * TS, M * TS), "XONIX");

	// load texture
	Texture t1;
	t1.loadFromFile("./assets/images/tiles.png");

	Sprite sTile(t1);


	int x = 0, y = 0, dx = 0, dy = 0;
	float timer = 0.f, delay = 0.07f;
	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
		}


		// keyboar input
		if (Keyboard::isKeyPressed(Keyboard::Left)) { dx = -1; dy = 0; }
		else if (Keyboard::isKeyPressed(Keyboard::Right)) { dx = 1; dy = 0; }
		else if (Keyboard::isKeyPressed(Keyboard::Up)) { dx = 0; dy = -1; }
		else if (Keyboard::isKeyPressed(Keyboard::Down)) { dx = 0; dy = 1; }

		if (timer > delay)
		{
			x += dx;
			y += dy;
			timer = 0;
		}

		////////draw////////////
		window.clear(Color::Black);

		sTile.setTextureRect(IntRect(36, 0, TS, TS));
		sTile.setPosition(x * TS, y * TS);
		window.draw(sTile);

		window.display();
	}
	return 0;
}