#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

const int TS = 54; // Title size
Vector2i offset(48, 24);

struct Piece
{
	int x, y, col, row, king, match, alpha;

	Piece() : match(0), alpha(255)
	{ }
}grid[10][10];

void swap(Piece p1, Piece p2)
{
	// swap were pieces shound be
	std::swap(p1.col, p2.col);
	std::swap(p1.row, p2.row);

	// swap main pieces
	grid[p1.row][p1.col] = p1;
	grid[p2.row][p2.col] = p2;
}

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

	int x0, y0, x, y; // pieces that are going to move
	int click = 0; // num of clicks
	Vector2i pos; // for mouse
	bool isSwap = false, isMoving = false; // for swap

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
					if (!isSwap && !isMoving) // move when swap othe pieces ended
						click++;
					pos = Mouse::getPosition(app) - offset;
				}
		}

		////mouse click/////
		if (click == 1)
		{
			// +1 because it star at index 1
			x0 = pos.x / TS + 1;
			y0 = pos.y / TS + 1;
		}
		else if (click == 2)
		{
			// +1 because it star at index 1
			x = pos.x / TS + 1;
			y = pos.y / TS + 1;
			if (abs(x - x0) + abs(y - y0) == 1) // verify if both pieces are near each other
			{
				swap(grid[y0][x0], grid[y][x]);
				isSwap = true;
				click = 0;
			}
			else
				click = 1;
		}

		// verify matching
		for (int i = 1; i < 9; i++)
			for (int j = 1; j < 9; j++)
			{
				// horizontaly
				if (grid[i][j].king == grid[i + 1][j].king)
					if (grid[i][j].king == grid[i - 1][j].king)
						for (int n = -1; n <= 1; n++)
							grid[i + n][j].match++;
				// verticaly
				if (grid[i][j].king == grid[i][j + 1].king)
					if (grid[i][j].king == grid[i][j - 1].king)
						for (int n = -1; n <= 1; n++)
							grid[i][j + n].match++;
			}

		// moving animation
		isMoving = false;
		for (int i = 1; i < 9; i++)
			for (int j = 1; j < 9; j++)
			{
				Piece & p = grid[i][j];
				int dx, dy;
				for (int i = 0; i < 4; i++) // x4 speed
				{
					dx = p.x - p.col * TS;
					dy = p.y - p.row * TS;
					if (dx)
						p.x -= dx / abs(dx);
					if (dy)
						p.y -= dy / abs(dy);
				}
				if (dx || dy)
					isMoving = true;
			}

		// deleting animation
		if (!isMoving)
			for (int i = 1; i < 9; i++)
				for (int j = 1; j < 9; j++)
					if (grid[i][j].match)
						if (grid[i][j].alpha > 10)
						{
							grid[i][j].alpha -= 10;
							isMoving = true;
						}

		// get score
		int score = 0;
		for (int i = 1; i < 9; i++)
			for (int j = 1; j < 9; j++)
				score += grid[i][j].match;

		// second swap if not valid
		if (isSwap && !isMoving) 
		{
			if (!score) // if there is no score
				swap(grid[y0][x0], grid[y][x]);
			isSwap = false;
		}

		// update grid
		if (!isMoving)
		{
			for (int i = 8; i > 0; i--)
				for (int j = 1; j < 9; j++)
					if (grid[i][j].match)
						for (int n = i; n > 0; n--)
							if (!grid[n][j].match)
							{
								swap(grid[n][j], grid[i][j]);
								break;
							}
			for (int j = 1; j < 9; j++)
				for (int i = 8, n = 0; i > 0; i--)
					if (grid[i][j].match)
					{
						// reset for a new peace
						grid[i][j].king = rand() % 7;
						grid[i][j].y = -TS * n++;
						grid[i][j].match = 0;
						grid[i][j].alpha = 255;
					}
		}

		//////draw/////
		app.clear();
		app.draw(sBackground);

		for (int i = 1; i < 9; i++)
			for (int j = 1; j < 9; j++)
			{
				sGem.setTextureRect(IntRect(grid[i][j].king * 49, 0, 49, 49));
				sGem.setColor(Color(255, 255, 255, grid[i][j].alpha));
				sGem.setPosition(grid[i][j].x, grid[i][j].y);
				sGem.move(offset.x - TS, offset.y - TS);
				app.draw(sGem);
			}

		app.display();
	}

	return 0;
}