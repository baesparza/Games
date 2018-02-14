#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

// options
unsigned const int w = 32; // size of each square
unsigned const int rows = 10, cols = 10;
unsigned const int number_bombs = 10;
int grid[rows][cols],
sgrid[rows][cols]; // for showing


void fill_bombs()
{
	for (int n = 0; n < number_bombs; n++)
	{
		int i = rand() % rows;
		int j = rand() % cols;
		if (grid[i][j] == 9)
			n--; // already has a bomb -> pass
		else
			grid[i][j] = 9;
	}
}

int update_bombs(int i, int j)
{
	int n = 0;
	return n;
}

int main()
{
	srand(time(0));

	RenderWindow app(VideoMode(rows * w, cols * w), "MinesWeeper");

	Texture t;
	t.loadFromFile("./assets/images/tiles.jpg");

	Sprite s(t);

	// fill grid with boid squares
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			sgrid[i][j] = 10;

	// fill with bombs
	fill_bombs();

	// know num of mines touching each square
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			if (grid[i][j] == 9) continue;

			// counter for mines
			grid[i][j] = update_bombs(i, j);
		}



	while (app.isOpen())
	{
		Vector2i pos = Mouse::getPosition(app);
		int x = pos.x / w;
		int y = pos.y / w;

		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();

			if (e.type == Event::MouseButtonPressed)
			{
				if (e.key.code == Mouse::Left)
					sgrid[x][y] = grid[x][y];
				else if (e.key.code == Mouse::Right)
					sgrid[x][y] = 11;
			}


		}

		app.clear(Color::White);

		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
			{
				if (sgrid[x][y] == 9) // show all grid / lose
					sgrid[i][j] = grid[i][j];
				s.setTextureRect(IntRect(sgrid[i][j] * w, 0, w, w));
				s.setPosition(i * w, j * w);
				app.draw(s);
			}
		app.display();
	}

	return 0;
}