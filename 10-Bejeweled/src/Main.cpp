#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

const int TS = 54; // Title size
Vector2i offset(48, 24);

struct Piece
{
	int x, y, col, row, king, match;

	Piece() : match(0)
	{

	}
}grid[10][10];

int main()
{
	srand(time(0));

	RenderWindow app(VideoMode(740, 480), "Bejeweled");
	app.setFramerateLimit(60);

	// load texture
	Texture t1, t2;
	t1.loadFromFile("./images/background.png");
	t2.loadFromFile("./images/gems.png");

	Sprite sBackground(t1), sGem(t2);


	// initialize grid
	for (int i = 1; i < 9; i++)
		for (int j = 1; j < 9; j++)
		{
			grid[i][j].king = rand() % 7;
			grid[i][j].col = j;
			grid[i][j].row = i;
			grid[i][j].x = j * TS;
			grid[i][j].y = i * TS;
		}

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
			if (e.type == Event::Closed)
				app.close();


		//////draw/////
		app.clear();
		app.draw(sBackground);

		for (int i = 1; i < 9; i++)
			for (int j = 1; j < 9; j++)
			{
				sGem.setTextureRect(IntRect(grid[i][j].king * 49, 0, 49, 49));
				sGem.setPosition(grid[i][j].x, grid[i][j].y);
				sGem.move(offset.x - TS, offset.y - TS);
				app.draw(sGem);
			}

		app.display();
	}

	return 0;
}