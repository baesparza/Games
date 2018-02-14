#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

// options
unsigned const int w = 32; // size of each square
unsigned const int rows = 10, cols = 10;
unsigned const int number_bombs = 30;
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

void update_bombs()
{
	// clone array of bombs
	int temp[rows + 2][cols + 2];

	// clone values to temporal array
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			temp[i + 1][j + 1] = grid[i][j];

	// know num of mines touching each square in the temp array
	for (int i = 1; i <= rows; i++)
		for (int j = 1; j <= cols; j++)
		{
			if (temp[i][j] == 9) continue;

			int n = 0;
			if (temp[i - 1][j - 1] == 9) n++; // top left
			if (temp[i - 1][j] == 9) n++; // top center
			if (temp[i - 1][j + 1] == 9) n++; // top right
			if (temp[i][j + 1] == 9) n++; // right center
			if (temp[i + 1][j + 1] == 9) n++; // bottom right
			if (temp[i + 1][j] == 9) n++; // bottom center
			if (temp[i + 1][j - 1] == 9) n++; // bottom left
			if (temp[i][j - 1] == 9) n++; // left center

			grid[i - 1][j - 1] = n; // update main grid
		}
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

	// fill with bombs and update near squares
	fill_bombs();
	update_bombs();


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


		/////draw//////
		app.clear(Color::White);

		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
			{
				if (x > 0 && x < w*rows && y > 0 && y < w*cols) // inside the window
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