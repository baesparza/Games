#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

const int N = 6;
const int TS = 54; // tile size
Vector2f offset(65, 55);

struct Pipe
{
	int orientation;
	float angle;
	bool on;

	Pipe() : angle(0)
	{ }
} grid[N][N];

int main()
{
	RenderWindow app(VideoMode(390, 390), "The Pipe Puzzle");
	app.setFramerateLimit(60);

	Texture t1, t2;
	t1.loadFromFile("./images/background.png");
	t2.loadFromFile("./images/pipes.png");

	Sprite sBackground(t1), sPipe(t2);
	sPipe.setOrigin(TS / 2, TS / 2);

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();

			if (e.type == Event::MouseButtonPressed)
				if (e.key.code == Mouse::Left)
				{
					Vector2i pos = Mouse::getPosition(app) + Vector2i(TS / 2, TS / 2) - Vector2i(offset);
					pos /= TS;
					grid[pos.x][pos.y].orientation++;
				}
		}


		/////draw/////
		app.clear();
		app.draw(sBackground);

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				// smoth rotation
				grid[j][i].angle += 5;
				if (grid[j][i].angle > grid[j][i].orientation * 90)
					grid[j][i].angle = grid[j][i].orientation * 90;

				// draw pipe
				sPipe.setTextureRect(IntRect(TS * 2, 0, TS, TS));
				sPipe.setRotation(grid[j][i].angle);
				sPipe.setPosition(j * TS, i * TS);
				sPipe.move(offset);
				app.draw(sPipe);
			}

		app.display();
	}

	return 0;
}