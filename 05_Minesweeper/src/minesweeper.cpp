#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;


int main()
{
	RenderWindow app(VideoMode(400, 400), "MinesWeeper");

	Texture t;
	t.loadFromFile("./assets/images/tiles.jpg");

	Sprite s(t);

	unsigned const int w = 32; // size of each square
	int grid[12][12],
		sgrid[12][12]; // for showing

		// fill grid with boid squares
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			sgrid[i][j] = 10;
			grid[i][j] = (rand() % 5 == 0) ? 9 : 0; // fill with mines or safe
		}

	// know num of mines touching each square
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			if (grid[i][j] == 9) continue;

			// counter for mines
			int n = 0;
			if (grid[i - 1][j - 1] == 9) n++; // top left
			if (grid[i - 1][j] == 9) n++; // top center
			if (grid[i - 1][j + 1] == 9) n++; // top right
			if (grid[i][j + 1] == 9) n++; // right center
			if (grid[i + 1][j + 1] == 9) n++; // bottom right
			if (grid[i + 1][j] == 9) n++; // bottom center
			if (grid[i + 1][j - 1] == 9) n++; // bottom left
			if (grid[i][j - 1] == 9) n++; // left center

			grid[i][j] = n;
		}



	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}

		app.clear(Color::White);

		for (int i = 1; i <= 10; i++)
			for (int j = 1; j <= 10; j++)
			{
				sgrid[i][j] = grid[i][j];
				s.setTextureRect(IntRect(sgrid[i][j] * w, 0, w, w));
				s.setPosition(i * w, j * w);
				app.draw(s);
			}
		app.display();
	}

	return 0;
}