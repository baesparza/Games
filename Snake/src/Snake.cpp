#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

unsigned const int N = 30, M = 20, // number of colums, rows
size = 16, // size of each square
Width = size * N, Height = size * M;


int main()
{
	RenderWindow app(VideoMode(Width, Height), "Snake Game!");

	Texture t1, t2;
	t1.loadFromFile("./assets/images/white.png");
	t2.loadFromFile("./assets/images/red.png");

	Sprite sprite1(t1), sprite2(t2);

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}


		////draw////
		app.clear();
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
			{
				sprite1.setPosition(i * size, j * size);
				app.draw(sprite1);
			}

		app.display();
	}

	return 0;
}