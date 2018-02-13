#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

int main()
{
	RenderWindow app(VideoMode(320, 320), "MinesWeeper");

	int w = 32;
	int grid[10][10], // 12 is used for offset
		sgrid[10][10]; // for showing

	Texture t;
	t.loadFromFile("./assets/images/tiles.jpg");

	Sprite s(t);


	// fill grid with boid squares
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			sgrid[i][j] = 10;


	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}

		app.clear(Color::White);

		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
			{
				s.setTextureRect(IntRect(sgrid[i][j] * w, 0, w, w));
				s.setPosition(i * w, j * w);
				app.draw(s);
			}
		app.display();
	}

	return 0;
}